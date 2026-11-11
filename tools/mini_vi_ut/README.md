# mini_vi_ut — VI + ISP unit test (pattern / sensor modes)

Merged from the original `isp_pattern` and `isp_sensor` binaries into a single
`isp_ut`. Mode and compress settings are driven by a config file in the
program's running directory (`isp_ut_cfg.ini`).

## Configuration

Place `isp_ut_cfg.ini` next to the binary (or in the CWD when launching):

```ini
# input: sensor | pattern (default: sensor)
input = sensor

# compress_mode: none | tile | line | frame (default: tile)
compress_mode = none
```

- `input` selects the VI source path.
- `compress_mode` sets the VI channel's DPCM compression (used on both pipe
  and channel attributes).
- Missing file or missing keys fall back to the defaults shown above. The
  resolved values are printed at startup so you can confirm what is in effect.

### Modes

| Mode | Description |
|---|---|
| `sensor` | Real sensor path: MIPI + sensor driver + pqbin load for 3A tuning. |
| `pattern` | VI pattern generator (no MIPI, no sensor driver). Synthesises frames in DRAM. |

## Files

| File | Description |
|---|---|
| `isp_ut.c` | Merged main + pattern/sensor mode entry points. Dispatches on argv[1]. |
| `isp_pattern_isp.c/.h` | ISP bring-up/teardown (shared by both modes). 3A register + pub attr + ISP run thread + daemon2 init/uninit. |
| `Makefile` | Builds `isp_ut` (RISC-V 64 static). |

## Build

```bash
# From isp-tool-daemon root:
make -C tools mini_vi_ut

# Or standalone:
cd tools/mini_vi_ut
make all
```

## Deploy (device /mnt/data)

```bash
# Required:
push to /mnt/data/:
  isp_ut
  isp_ut_cfg.ini                             # config (see above)
  <SDK>/modules/isp/cv190x/isp-daemon2/rpc.json   # readall/writeall need this
  /mnt/data/sensor_cfg.ini                         # geometry + sensor type

# Optional:
  /mnt/sd/cvi_sdr.bin or cvi_wdr.bin               # pqbin (sensor mode only)
```

### sensor_cfg.ini requirements

- **pattern mode**: `enSnsType` must be one of the supported types (IMX327,
  GC4653, SC500AI, OS04A10, SC2331_1L, etc.)
- **sensor mode**: must match a supported sensor driver

## Run

```bash
cd /mnt/data

# Make sure loopback is up (needed for JSON-RPC client connections)
ifconfig lo up

# Start isp_ut (reads ./isp_ut_cfg.ini for mode + compress_mode)
./isp_ut &

# Then use ispd2_client to interact:
ispd2_client readall     # -> /mnt/data/isp_readall.json
ispd2_client writeall    # read -> write loopback
ispd2_client dumpyuv     # -> /mnt/data/isp_dump.yuv
ispd2_client dumpraw     # -> /mnt/data/isp_dump.raw
ispd2_client dumpall     # = dumpyuv + dumpraw
ispd2_client exportbin   # -> /mnt/data/isp_params.bin
ispd2_client importbin   # load from /mnt/data/isp_params.bin
ispd2_client exit        # triggers graceful shutdown (creates /mnt/data/isp_test_ut_exit)
```

## Exit mechanism

`isp_ut` sits in a loop checking for `/mnt/data/isp_test_ut_exit`. When the
file appears (created by `ispd2_client exit`), it removes the trigger and runs
full teardown: VI stop -> ISP exit -> daemon2 uninit -> VB exit -> SYS exit.

## Compress mode

Set via `isp_ut_cfg.ini` (see Configuration section above). Default is `tile`.

## Verification checklist

- [ ] `isp_ut` prints `Get frame OK <WxH>` (self-check passed)
- [ ] `isp_ut` prints `isp daemon2 listening on 127.0.0.1:5566`
- [ ] `ispd2_client readall` saves 59 modules, valid JSON
- [ ] `ispd2_client writeall` prints `N ok, M failed, K skipped`
- [ ] `ispd2_client dumpyuv` produces `isp_dump.yuv` with size = W x H x 3/2
- [ ] `ispd2_client dumpraw` produces `isp_dump.raw` + Reg/AE/AWB log
- [ ] `ispd2_client exportbin` produces `isp_params.bin`
- [ ] `ispd2_client importbin` applies same byte count
- [ ] `ispd2_client exit` -> `isp_ut` prints `exit trigger detected` and `exited cleanly`

## Common issues

| Symptom | Cause / Fix |
|---|---|
| `patgen getconfig failed` | sensor_cfg.ini `enSnsType` not in supported list |
| `connect refused` | daemon2 not up: confirm isp_ut is running, port 5566 |
| `readall` lots of NG | ISP hasn't output frame yet (wait for self-check OK); or module not supported in patgen |
| `dumpyuv` NONE | VI channel no frame: confirm self-check passed |
| `rpc.json not found` | readall/writeall need rpc.json on device |
