#!/usr/bin/env python3
"""Capture RAW bayer frames from phobos3 isp_tool_daemon (JSONRPC :5566).

Protocol (server: cvi_mpi/modules/isp/cv190x/isp-daemon2/src/cvi_ispd2_callback_funcs_apps.c):
  CVI_SetTopInfo -> CVI_GetMultipleRAWFrame -> CVI_GetBinaryInfo/GetBinaryData (AE/AWB bin,
  BINARY_OUTPUT_MODE: raw binary, no JSON) -> CVI_GetImageData * N -> CVI_StopGetImageData

Usage:
  python3 capture_raw_phobos3.py [--host 192.168.50.102] [--port 5566] [--frames 1]
                               [--save-dir DIR] [--no-unpack]
Unpack: packed12/dpcm6 -> uint16 (numpy); default on.

NOTE: when daemon runs with cfg.json compress-mode "tile" (default), the
dumped raw is DPCM6 (compress=1, w*h*3/4 bytes). Keep --no-unpack to save the
original dpcm6 bytes (replay them with replay.json CompressMode "tile");
default u16 output is for packed12 replay (CompressMode "none") or analysis.

Known upstream gap: TRAWHeader exposure/AGain/DGain fields are 0 in linear
mode (UpdateRAWHeader reads u32LongExpTime which is 0 for linear). The replay
script sanitizes zeros, so round-trip still works.
"""
import argparse
import json
import logging
import os
import socket
import struct
import sys
from datetime import datetime

import numpy as np

DEFAULT_HOST = "192.168.50.102"
DEFAULT_PORT = 5566
BAYER_STR = ["BGGR", "GBRG", "GRBG", "RGGB"]
BIN_DATA_AE = 1
BIN_DATA_AWB = 2

# packed struct, 112 bytes total (matches TRAWHeader in isp-daemon2)
TRAW_HEADER_FMT = "<BxHHHHHBBBxHHBxxxIIIIIIIHHhhhhhhhhhHHHHHHHHxxIIIHHI"

_id_counter = 0
_log = logging.getLogger("capture_raw")


def next_id():
    global _id_counter
    _id_counter += 1
    return _id_counter


def recv_all(sock, size, timeout=120):
    sock.settimeout(timeout)
    data = b""
    while len(data) < size:
        chunk = sock.recv(min(size - len(data), 65536))
        if not chunk:
            break
        data += chunk
    if len(data) < size:
        raise ConnectionError("recv_all: got %d/%d bytes" % (len(data), size))
    return data


def recv_jsonrpc_response(sock, timeout=60):
    sock.settimeout(timeout)
    buf = b""
    bracket = square = 0
    while True:
        chunk = sock.recv(4096)
        if not chunk:
            raise ConnectionError("connection closed")
        buf += chunk
        for b in chunk:
            if b == ord("{"):
                bracket += 1
            elif b == ord("}"):
                bracket -= 1
            elif b == ord("["):
                square += 1
            elif b == ord("]"):
                square -= 1
        if bracket == 0 and square == 0 and buf:
            return json.loads(buf)


def send_jsonrpc(sock, method, params=None):
    req = {"jsonrpc": "2.0", "method": method, "id": next_id()}
    if params is not None:
        req["params"] = params
    sock.sendall(json.dumps(req).encode())


def parse_raw_header(data):
    size = struct.calcsize(TRAW_HEADER_FMT)
    if len(data) < size:
        raise ValueError("TRAWHeader too small: %d < %d" % (len(data), size))
    f = struct.unpack(TRAW_HEADER_FMT, data[:size])
    return {
        "numFrame": f[0], "width": f[1], "height": f[2],
        "stride": [f[3], f[4], f[5]], "curFrame": f[6], "bayerID": f[7],
        "compress": f[8], "cropX": f[9], "cropY": f[10], "fusionFrame": f[11],
        "exposure": [f[12], f[13], f[14], f[15]], "ispDGain": f[16],
        "iso": f[17], "colorTemp": f[18], "wbRGain": f[19], "wbBGain": f[20],
        "ccm": list(f[21:30]), "blcOffset": list(f[30:34]),
        "blcGain": list(f[34:38]), "exposureRatio": f[38],
        "exposureAGain": f[39], "exposureDGain": f[40],
        "cropWidth": f[41], "cropHeight": f[42], "size": f[43],
        "header_size": size,
    }


def unpack_packed12(data, width, height):
    npix = width * height
    if len(data) < npix * 3 // 2:
        raise ValueError("packed12 too small: %d < %d" % (len(data), npix * 3 // 2))
    arr = np.frombuffer(data[: npix * 3 // 2], dtype=np.uint8)
    v0, v1, v2 = arr[0::3], arr[1::3], arr[2::3]
    p0 = (v0.astype(np.uint16) << 4) | (v2 & 0x0F)
    p1 = (v1.astype(np.uint16) << 4) | (v2 >> 4)
    out = np.zeros(npix, dtype=np.uint16)
    out[0::2] = p0
    out[1::2] = p1
    return out


def _decode_12_6_12(nop, xenco, xpred):
    if nop:
        return (xenco << 6) + 32
    if (xenco & 0x3C) == 0x00:
        return max(xpred - (xenco & 0x1), 0) if (xenco & 0x2) else min(xpred + (xenco & 0x1), 4095)
    if (xenco & 0x3C) == 0x04:
        v = ((xenco & 0x1) << 2) + 3
        return max(xpred - v, 0) if (xenco & 0x2) else min(xpred + v, 4095)
    if (xenco & 0x38) == 0x10:
        v = ((xenco & 0x3) << 3) + 13
        return max(xpred - v, 0) if (xenco & 0x4) else min(xpred + v, 4095)
    if (xenco & 0x3C) == 0x08:
        v = ((xenco & 0x1) << 4) + 49
        return max(xpred - v, 0) if (xenco & 0x2) else min(xpred + v, 4095)
    if (xenco & 0x38) == 0x18:
        v = ((xenco & 0x3) << 5) + 89
        return max(xpred - v, 0) if (xenco & 0x4) else min(xpred + v, 4095)
    if (xenco & 0x3C) == 0x0C:
        v = ((xenco & 0x1) << 6) + 233
        return max(xpred - v, 0) if (xenco & 0x2) else min(xpred + v, 4095)
    v = (xenco & 0x1F) << 7
    return v + 63 if v > xpred else v + 64


def _predictor2(x, pb):
    if x == 0:
        return 0, True
    if x == 1:
        return pb[0], False
    if x == 2:
        return pb[1], False
    if x == 3:
        return (pb[0] if (pb[0] <= pb[1] <= pb[2]) or (pb[0] >= pb[1] >= pb[2]) else pb[1]), False
    if (pb[0] <= pb[1] <= pb[2]) or (pb[0] >= pb[1] >= pb[2]):
        return pb[0], False
    if (pb[0] <= pb[2] and pb[1] <= pb[3]) or (pb[0] >= pb[2] and pb[1] >= pb[3]):
        return pb[1], False
    return (pb[1] + pb[3] + 1) >> 1, False


def unpack_dpcm6(data, width, height):
    npix = width * height
    if len(data) < npix * 3 // 4:
        raise ValueError("dpcm6 too small")
    n_groups = npix // 4
    src6 = np.zeros(npix, dtype=np.uint16)
    arr = np.frombuffer(data[: n_groups * 3], dtype=np.uint8)
    v0 = arr[0::3].astype(np.uint16)
    v1 = arr[1::3].astype(np.uint16)
    v2 = arr[2::3].astype(np.uint16)
    src6[0::4] = ((v0 & 0x03) << 4) | (v2 & 0x0F)
    src6[1::4] = (v0 & 0xFC) >> 2
    src6[2::4] = ((v1 & 0x03) << 4) | (v2 >> 4)
    src6[3::4] = (v1 & 0xFC) >> 2
    out = np.zeros(npix, dtype=np.uint16)
    pb = [0, 0, 0, 0]
    idx = 0
    for y in range(height):
        for x in range(width):
            xpred, nop = _predictor2(x, pb)
            xd = _decode_12_6_12(nop, int(src6[idx]), xpred)
            out[idx] = xd
            pb[3], pb[2], pb[1], pb[0] = pb[2], pb[1], pb[0], xd
            idx += 1
    return out


def unpack_raw(data, hdr):
    if hdr["compress"] == 0:
        return unpack_packed12(data, hdr["width"], hdr["height"])
    if hdr["compress"] == 1:
        return unpack_dpcm6(data, hdr["width"], hdr["height"])
    npix = hdr["width"] * hdr["height"]
    return np.frombuffer(data[: npix * 2], dtype=np.uint16).copy()


def capture(host, port, frames, tightly, dump_reg, dump_raw, save_dir,
            timeout, unpack):
    sock = socket.create_connection((host, port), timeout=10)
    try:
        send_jsonrpc(sock, "CVI_SetTopInfo",
                     {"ViPipe": 0, "ViChn": 0, "VpssGrp": 0, "VpssChn": 0})
        recv_jsonrpc_response(sock, timeout)

        send_jsonrpc(sock, "CVI_GetMultipleRAWFrame",
                     {"frames": frames, "tightly": tightly,
                      "dump_reg": dump_reg, "dump_raw": dump_raw})
        resp = recv_jsonrpc_response(sock, timeout)
        if "error" in resp:
            _log.error("GetMultipleRAWFrame: %s", resp["error"])
            return None
        p = resp.get("result", {}).get("params", {})
        raw_size = p.get("Data size", 0)
        reg_log = p.get("Reg dump log", "")
        raw_info_log = p.get("Raw info log", "")
        ae_log = p.get("AE log", "")
        awb_log = p.get("AWB log", "")
        _log.info("data_size=%d bayer=%s iso=%s crop=%sx%s",
                  raw_size, p.get("Bayer ID"), p.get("Iso"),
                  p.get("Crop Width"), p.get("Crop Height"))

        bins = {}
        for name, content in (("ae", BIN_DATA_AE), ("awb", BIN_DATA_AWB)):
            send_jsonrpc(sock, "CVI_GetBinaryInfo", {"content": content})
            r = recv_jsonrpc_response(sock, timeout)
            sz = r.get("result", {}).get("params", {}).get("Data size", 0)
            send_jsonrpc(sock, "CVI_GetBinaryData", {"content": content})
            # BINARY_OUTPUT_MODE: raw binary direct, no JSON response
            bins[name] = recv_all(sock, sz, timeout) if sz > 0 else recv_all(sock, 4, timeout)

        frames_out = []
        if raw_size:
            while True:
                send_jsonrpc(sock, "CVI_GetImageData")
                data = recv_all(sock, raw_size, timeout)
                hdr = parse_raw_header(data)
                frames_out.append((hdr, data[hdr["header_size"]:]))
                _log.info("frame %d/%d %dx%d bayer=%d compress=%d size=%d",
                          hdr["curFrame"], hdr["numFrame"], hdr["width"],
                          hdr["height"], hdr["bayerID"], hdr["compress"], hdr["size"])
                if hdr["curFrame"] >= hdr["numFrame"] - 1:
                    break

        send_jsonrpc(sock, "CVI_StopGetImageData")
        try:
            recv_jsonrpc_response(sock, timeout=5)
        except Exception:
            pass
    finally:
        sock.close()

    if not frames_out:
        _log.error("no raw frames captured")
        return None

    hdr = frames_out[0][0]
    dt = datetime.now().strftime("%Y%m%d%H%M%S")
    out_dir = os.path.join(save_dir or ".", dt)
    os.makedirs(out_dir, exist_ok=True)
    bayer = BAYER_STR[hdr["bayerID"]] if hdr["bayerID"] < 4 else "UNK%d" % hdr["bayerID"]
    w, h = hdr["cropWidth"] or hdr["width"], hdr["cropHeight"] or hdr["height"]
    base = "%dX%d_%s_Linear_-color=%d_-bits=12_-frame=%d_hdr=%d_ISO=%d_%s" % (
        w, h, bayer, hdr["bayerID"], frames, hdr["fusionFrame"], hdr["iso"], dt)

    raw_path = os.path.join(out_dir, base + ".raw")
    with open(raw_path, "wb") as f:
        for h2, pix in frames_out:
            f.write(unpack_raw(pix[: h2["size"]], h2).tobytes()
                    if unpack else pix[: h2["size"]])
    _log.info("saved %s", raw_path)

    for suffix, content in ((".txt", raw_info_log), (".json", reg_log),
                            ("-aelog.txt", ae_log), ("-awblog.txt", awb_log),
                            ("-ae.bin", bins.get("ae", b"")),
                            ("-awb.wbin", bins.get("awb", b""))):
        if content:
            with open(os.path.join(out_dir, base + suffix), "wb") as f:
                f.write(content.encode() if isinstance(content, str) else content)

    meta = {k: v for k, v in hdr.items() if k != "header_size"}
    meta["file"] = raw_path
    with open(os.path.join(out_dir, "meta.json"), "w") as f:
        json.dump(meta, f, indent=2)
    _log.info("meta: %s", json.dumps({k: meta[k] for k in
               ("width", "height", "bayerID", "compress", "iso", "size")}))
    return raw_path


def main():
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    ap = argparse.ArgumentParser()
    ap.add_argument("--host", default=DEFAULT_HOST)
    ap.add_argument("--port", type=int, default=DEFAULT_PORT)
    ap.add_argument("--frames", type=int, default=1)
    ap.add_argument("--no-tightly", action="store_true")
    ap.add_argument("--no-dump-reg", action="store_true")
    ap.add_argument("--no-dump-raw", action="store_true")
    ap.add_argument("--save-dir", default="/tmp/opencode/raws")
    ap.add_argument("--timeout", type=int, default=120)
    ap.add_argument("--no-unpack", action="store_true",
                    help="save raw as-is (packed12/dpcm6)")
    args = ap.parse_args()
    ret = capture(args.host, args.port, args.frames, not args.no_tightly,
                  not args.no_dump_reg, not args.no_dump_raw, args.save_dir,
                  args.timeout, not args.no_unpack)
    sys.exit(0 if ret else 1)


if __name__ == "__main__":
    main()
