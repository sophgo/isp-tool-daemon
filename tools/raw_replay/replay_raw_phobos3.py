#!/usr/bin/env python3
"""Replay RAW frames to phobos3 isp_tool_daemon in raw-replay mode (JSONRPC :5566).

Protocol (server: cvi_mpi/modules/isp/cv190x/isp-daemon2/src/
  cvi_ispd2_callback_funcs_apps_rawreplay.c + cvi_ispd2_message.c):
  per frame:
    CVI_SetBinaryData {content:4, size:N, ...raw_* meta...}  -> JSON resp
    send N raw bytes (binary input mode, daemon counts exactly N bytes)
                                                            -> JSON resp
  then CVI_ISP_StartRawReplay -> replay thread feeds VI via SendPipeRaw

Daemon must be started in replay mode (./CviIspTool.sh -r) with replay.json
Width/Height/BayerFormat matching the raw (RecvRawReplayDataInfo checks ISP
pub attr == raw meta) and CompressMode matching the pixel data format:
  - u16/packed12 input  -> replay.json "CompressMode": "none" (BE reads packed12, 2880B/row)
  - dpcm6 input         -> replay.json "CompressMode": "tile" (BE reads dpcm6, 1440B/row)
NOTE: replay.json is read at daemon start; changing it requires daemon restart.

AE metadata zeros crash libae (div-by-zero SIGFPE kills daemon): this script
sanitizes exposure/gain fields (>=1024 Q10 gains, 10000us exp, ratio>=128).

Usage:
  python3 replay_raw_phobos3.py --raw FILE.raw [--meta FILE.json] [--host IP]
                              [--frames N] [--cancel]
FILE.raw: uint16 (unpacked) / packed12 / dpcm6; auto-detected by size.
Verify with FILE-BASED decode (live RTSP join shows grey concealment frames):
  ffmpeg -rtsp_transport tcp -i rtsp://IP:8554/stream0 -t 5 -c copy out.h265
  ffmpeg -i out.h265 -vf signalstats,metadata=print -f null - 2>&1 | grep YAVG
"""
import argparse
import json
import logging
import os
import socket
import struct
import sys
import time

DEFAULT_HOST = "192.168.50.102"
DEFAULT_PORT = 5566
BIN_DATA_RAW = 4

_id = 0
_log = logging.getLogger("replay_raw")


def next_id():
    global _id
    _id += 1
    return _id


def recv_all(sock, size, timeout=180):
    sock.settimeout(timeout)
    data = b""
    while len(data) < size:
        chunk = sock.recv(min(size - len(data), 1 << 20))
        if not chunk:
            raise ConnectionError("recv_all %d/%d" % (len(data), size))
        data += chunk
    return data


def recv_jsonrpc(sock, timeout=180):
    sock.settimeout(timeout)
    buf = b""
    bracket = square = 0
    while True:
        chunk = sock.recv(65536)
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


def call(sock, method, params=None, timeout=180):
    req = {"jsonrpc": "2.0", "method": method, "id": next_id()}
    if params is not None:
        req["params"] = params
    sock.sendall(json.dumps(req).encode())
    resp = recv_jsonrpc(sock, timeout)
    if "error" in resp:
        raise RuntimeError("%s -> %s" % (method, resp["error"]))
    return resp


def pack_u16_to_packed12(u16):
    """uint16 (little endian, 12bit valid) -> packed12 (3 bytes / 2 pixels)."""
    import numpy as np

    a = np.frombuffer(u16, dtype="<u2").astype(np.uint16) & 0x0FFF
    if a.size % 2:
        a = np.concatenate([a, np.zeros(1, dtype=np.uint16)])
    p0, p1 = a[0::2], a[1::2]
    n = p0.size
    out = np.zeros(n * 3, dtype=np.uint8)
    out[0::3] = (p0 >> 4).astype(np.uint8)
    out[1::3] = (p1 >> 4).astype(np.uint8)
    out[2::3] = ((p0 & 0x0F) | ((p1 & 0x0F) << 4)).astype(np.uint8)
    return out.tobytes()


def send_frame(sock, idx, total, meta, frame_bytes):
    params = {
        "content": BIN_DATA_RAW,
        "size": len(frame_bytes),
        "pixformat": 0,
        "raw_numFrame": total,
        "raw_curFrame": idx,
        "raw_width": meta["width"],
        "raw_height": meta["height"],
        "raw_bayerID": meta["bayerID"],
        "raw_enWDR": meta.get("enWDR", 0),
        "raw_ISO": meta.get("iso", 100),
        "raw_lightValueX100": int(meta.get("lightValue", 0) * 100),
        "raw_colorTemp": meta.get("colorTemp", 5000),
        "raw_ispDGain": meta.get("ispDGain", 1024),
        "raw_exposureRatio": max(meta.get("exposureRatio", 128), 128),
        "raw_exposureAGain": meta.get("exposureAGain", 1024),
        "raw_exposureDGain": meta.get("exposureDGain", 1024),
        "raw_longExposure": meta.get("longExposure", meta.get("exposure", [10000, 0])[0]),
        "raw_shortExposure": meta.get("shortExposure", meta.get("exposure", [10000, 0])[1]),
        "raw_AGainSF": meta.get("AGainSF", 1024),
        "raw_DGainSF": meta.get("DGainSF", 1024),
        "raw_ispDGainSF": meta.get("ispDGainSF", 1024),
        "raw_WB_RGain": meta.get("wbRGain", 1024),
        "raw_WB_GGain": meta.get("wbGGain", 1024),
        "raw_WB_BGain": meta.get("wbBGain", 1024),
        "raw_size": len(frame_bytes),
        "raw_roiFrameNum": 0,
        "raw_stRoiRect.s32X": 0,
        "raw_stRoiRect.s32Y": 0,
        "raw_stRoiRect.u32Width": 0,
        "raw_stRoiRect.u32Height": 0,
        "raw_roiFrameSize": 0,
        "raw_op_mode": 0,
        "raw_BLCOffset": meta.get("blcOffset", [0, 0, 0, 0]),
        "raw_BLCGain": meta.get("blcGain", [1024, 1024, 1024, 1024]),
    }
    call(sock, "CVI_SetBinaryData", params)
    sock.sendall(frame_bytes)  # exactly size bytes -> binary input mode
    resp = recv_jsonrpc(sock)
    if "error" in resp:
        raise RuntimeError("binary frame %d: %s" % (idx, resp["error"]))
    return resp


def main():
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    ap = argparse.ArgumentParser()
    ap.add_argument("--host", default=DEFAULT_HOST)
    ap.add_argument("--port", type=int, default=DEFAULT_PORT)
    ap.add_argument("--raw", required=True, help="raw file (u16 or packed12)")
    ap.add_argument("--meta", default=None, help="meta.json from capture script")
    ap.add_argument("--width", type=int, default=1920)
    ap.add_argument("--height", type=int, default=1080)
    ap.add_argument("--bayer", type=int, default=3, help="0 BGGR 1 GBRG 2 GRBG 3 RGGB")
    ap.add_argument("--frames", type=int, default=0,
                    help="replay frame count (0 = all in file, min 1)")
    ap.add_argument("--cancel", action="store_true", help="only send CVI_ISP_CancelRawReplay")
    args = ap.parse_args()

    meta = {"width": args.width, "height": args.height, "bayerID": args.bayer}
    if args.meta and os.path.exists(args.meta):
        with open(args.meta) as f:
            m = json.load(f)
        for k in ("width", "height", "bayerID", "iso", "colorTemp", "ispDGain",
                  "exposureRatio", "exposureAGain", "exposureDGain", "exposure",
                  "wbRGain", "wbBGain", "blcOffset", "blcGain"):
            if k in m:
                meta[k] = m[k]
        if "wbGGain" not in meta:
            meta["wbGGain"] = 1024

    # sanitize AE metadata: zeros crash libae (div-by-zero -> SIGFPE -> daemon dies)
    gain_1x = 1024  # Q10
    meta["exposureAGain"] = meta.get("exposureAGain") or gain_1x
    meta["exposureDGain"] = meta.get("exposureDGain") or gain_1x
    meta["ispDGain"] = meta.get("ispDGain") or gain_1x
    meta["longExposure"] = (meta.get("exposure", [0, 0])[0]
                            or meta.get("longExposure") or 10000)  # us
    meta["shortExposure"] = (meta.get("exposure", [0, 0])[1]
                             or meta.get("shortExposure") or 10000)
    meta["exposureRatio"] = max(meta.get("exposureRatio") or 128, 128)
    if not meta.get("lightValue"):
        meta["lightValue"] = 8.0
    if not meta.get("wbRGain"):
        meta["wbRGain"] = gain_1x
    if not meta.get("wbGGain"):
        meta["wbGGain"] = gain_1x
    if not meta.get("wbBGain"):
        meta["wbBGain"] = gain_1x
    meta.setdefault("blcGain", [gain_1x] * 4)

    sock = socket.create_connection((args.host, args.port), timeout=10)
    try:
        call(sock, "CVI_SetTopInfo",
             {"ViPipe": 0, "ViChn": 0, "VpssGrp": 0, "VpssChn": 0})

        if args.cancel:
            call(sock, "CVI_ISP_CancelRawReplay")
            _log.info("cancel sent")
            return 0

        raw = open(args.raw, "rb").read()
        npix = args.width * args.height
        if len(raw) >= npix * 2:
            _log.info("input looks uint16, repacking to packed12")
            data = pack_u16_to_packed12(raw)
            fsz = npix * 3 // 2
        elif len(raw) >= npix * 3 // 2:
            data = raw  # assume packed12 already
            fsz = npix * 3 // 2
        else:
            # dpcm6 (6bit/px, 3 bytes per 4 pixels): pass through as-is,
            # daemon pipe must be configured CompressMode "tile"
            data = raw
            fsz = npix * 3 // 4
            if len(data) < fsz:
                _log.error("raw too small: %d < %d", len(data), fsz)
                return 1
            _log.info("input looks dpcm6 (%d bytes), pass-through", len(data))

        nframes = max(args.frames, 1) if args.frames else max(len(data) // fsz, 1)
        _log.info("replaying %d frame(s) of %d bytes (bayer %d, %dx%d)",
                  nframes, fsz, args.bayer, args.width, args.height)

        t0 = time.time()
        for i in range(nframes):
            fb = data[i * fsz:(i + 1) * fsz]
            if len(fb) < fsz:
                fb = fb + bytes(fsz - len(fb))
            send_frame(sock, i, nframes, meta, fb)
            _log.info("frame %d/%d sent (%.1fs)", i + 1, nframes, time.time() - t0)

        call(sock, "CVI_ISP_StartRawReplay")
        _log.info("raw replay started, check rtsp://%s:8554/stream0", args.host)
    finally:
        sock.close()
    return 0


if __name__ == "__main__":
    sys.exit(main())
