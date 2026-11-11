# isp_test_client — isp daemon2 JSON-RPC 客户端

连接已运行的 isp daemon2 server（默认 `127.0.0.1:5566`），执行
readall / writeall / dumpyuv / dumpraw / exportbin / importbin /
mmapen / mmapget。

服务端（`isp_test_ut` 或真实 `ispd2` daemon）需要**先在本机或目标板上
启动**；本客户端只负责发起 JSON-RPC 2.0 调用。

## 文件

| 文件 | 说明 |
|---|---|
| `ispd2_client.c/.h` | RPC 传输层：TCP + 括号配平成帧 + 二进制收发 |
| `isp_test_client.c` | CLI：readall / writeall / dumpyuv / dumpraw / exportbin / importbin / mmapen / mmapget |

## 编译（host 端）

```bash
./build.sh
```

产物：`isp_test_client`（RISC-V 64 / ARM 静态链接，视 SDK）。

注意：Makefile 参数全部来自环境变量（build.sh 已设好），不要
`make PARAM_FILE=...` 方式调用（会破坏条件 include）。

## 部署（设备端 /mnt/data）

```bash
push 到 /mnt/data/:
  isp_test_client
  rpc.json                                          # readall/writeall 需要
  dump_cfg.ini                                      # dumpraw/dumpall 可选配置
```

## 运行（设备端）

先确保 ispd2 server 已经在监听（例如 `isp_test_ut` 或系统 daemon）：

```bash
cd /mnt/data
./isp_test_client readall  # → /mnt/data/isp_readall.json
./isp_test_client writeall # read→write 回环
./isp_test_client dumpyuv  # → /mnt/data/isp_dump.yuv（固定路径）
./isp_test_client dumpraw  # → /mnt/data/dumpraw_<YYYYmmdd_HHMMSS>/
                           #   含: isp_reg_dump.json + 3 个 log
./isp_test_client dumpall  # → /mnt/data/dumpall_<YYYYmmdd_HHMMSS>/
                           #   含: isp_dump.yuv + isp_reg_dump.json + 3 个 log
./isp_test_client exportbin# → /mnt/data/isp_params.bin
./isp_test_client importbin# 从 /mnt/data/isp_params.bin 导入
./isp_test_client mmapen 1  # 打开 TNR MO 运动图快照门控（sticky）
./isp_test_client mmapen 0  # 关闭（不做快照，实时路径零开销）
./isp_test_client mmapget   # → /mnt/data/isp_momap.bin（纯 2bpp 数据，无头）
                            #   并打印 w/h/stride/format/frame 与 0..3 直方图
```

可选参数：`--ip`（默认 127.0.0.1）、`--port`（默认 5566）、
`--rpc`（rpc.json 路径，默认 ./rpc.json → /mnt/data/rpc.json）、
`--out`（dumpyuv / mmapget 的输出文件路径）。

## mmapen / mmapget（TNR MO 运动图）

- `mmapen 1` 打开 libisp 的逐帧 MO 运动图（MoMp）快照，
  1080p 下每帧多一次 ~130KB cache invalidate + copy，验证完请 `mmapen 0` 关掉。
  门控是 **sticky** 的（直到 `mmapen 0` 或 daemon 退出），并且 daemon 会把它
  OR 进 telemetry 的 MoMap 页开关，不会被 telemetry 的 1Hz 自愈重推关掉。
- **`mmapen 0` 只关 RPC 这一路**：若 telemetry 的 MoMap 页开着
  （`CVI_SetTelemetryAttr {"MoMap":1}`），门控仍是 ON（OR 语义）。
  要彻底停掉快照，需同时把 MoMap 页关掉（`CVI_SetTelemetryAttr {"MoMap":0}`）
  或停掉 telemetry。
- `mmapget` 是两段式：先 `CVI_ISP_GetMmapSts` 拿 info 并 latch 一帧快照，
  再 `CVI_ISP_GetMmapStsData` 取回同一帧（客户端保证两步数据一致）。
- 落盘文件 = **纯 2bpp 打包 payload（无 16B 头）**，大小等于打印的 `Data size`；
  几何信息（w / h / stride / format / frame）看打印的 `mo map:` info 行。
  2bpp 值语义 0=still / 1=transition / 2=motion / 3=reserved，与 telemetry
  0xA0 的像素打包方式相同。
- 客户端**不设 pipe**：用 daemon session 的默认 pipe（0）。
- 失败常见原因：pipe 没在出流、3DNR 关闭（kernel 不建 MO buffer）、
  或忘了先 `mmapen 1`（快照未开启时 `CVI_ISP_GetMmapSts` 失败）。

## dump_cfg.ini（可选）

`dumpraw` / `dumpall` 的入参。不写则使用默认值。路径固定：
`/mnt/data/dump_cfg.ini`；找不到就用默认值。

```ini
# 抓帧数（daemon 在非 tightly 模式只支持 1）
frames=1
# 是否 tightly 模式（多帧打包成一段连续 buffer 一次传出）
tightly=0
# 是否抓 ISP 寄存器 dump（Reg dump log）
dump_reg=1
# 是否抓 raw 像素数据（Data size / binary stream）
dump_raw=1
# 客户端是否把 raw 写到 /mnt/data/isp_dump.raw
#   =0 只跑通整条链路 + 打印 header 统计，不落盘（排查用，默认）
#   =1 写文件
save_raw=0
```

`dumpall` 直接复用同一份配置。

## 验证清单

- [ ] `readall` 保存 59 个模块（58 ISP GET + GammaCurveByType），
      `cat /mnt/data/isp_readall.json` 是合法 JSON
- [ ] `writeall` 大部分模块 OK；个别模块 NG（如 daemon 不支持）可接受，
      打印统计 `N ok, M failed, K skipped`
- [ ] `dumpyuv` 后 `isp_dump.yuv` 大小 = W×H×3/2（固定路径）
- [ ] `dumpraw` 后新建 `/mnt/data/dumpraw_<时间戳>/` 目录，含
      `isp_reg_dump.json` / `isp_raw_info.log` / `isp_ae.log` / `isp_awb.log`
      （save_log=1）；若 save_raw=1 还会写 `isp_dump.raw`
- [ ] `dumpall` 后新建 `/mnt/data/dumpall_<时间戳>/` 目录，含 **全部 5 个文件**：
      `isp_dump.yuv` + `isp_reg_dump.json` + 3 个 log
- [ ] `exportbin` 后 `isp_params.bin` 大小 = 打印的 Data size
- [ ] `importbin` 打印 applied N bytes（与 exportbin 大小一致）
- [ ] `mmapen 1` 后 `mmapget` 打印 `mo map info` 且保存 `isp_momap.bin`，
      文件大小 = 打印的 Data size；`mmapen 0` 后再 `mmapget` 应失败

## 常见问题

| 现象 | 原因/处理 |
|---|---|
| connect refused | daemon2 没起来：确认 ispd2 server 在跑、端口 5566 |
| readall 大量 NG | ISP 尚未出帧；或该模块 patgen 下不支持 |
| dumpyuv 报 NONE | VI chn 无帧：确认 server 端已 Get frame OK |
| rpc.json not found | readall/writeall 需要把 rpc.json 推到设备 |
