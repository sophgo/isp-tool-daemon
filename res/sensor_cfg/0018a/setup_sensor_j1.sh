#!/bin/sh
# SC2331 on J1 connector (WEVB-0018A-V01 pg10), WiFi occupies dedicated SD1 pads (pg4 pin51-56)
#
# J1 wiring (vs J2, lane order is MIRRORED):
#   sensor CLK -> J1 B12/B13 -> MIPI_RX0_5P/N_0 -> pads MIPIRX5N/P (PHY lane 5)
#   sensor D0  -> J1 B15/B16 -> MIPI_RX0_4P/N_0 -> pads MIPIRX4N/P (PHY lane 4)
#   sensor D1  -> J1 B18/B19 -> MIPI_RX0_3P/N_0 -> pads MIPIRX3N/P (PHY lane 3)
#   i2c        -> J1 A8/A9   -> I2C2_SDA/SCL    -> pads MIPI_TXM1/TXP1 (same as J2)
#   mclk       -> J1 B30/B31 -> CAM_MCLK1       -> pad MIPI_TXM0 (J2 was CAM_MCLK0/MIPI_TXP0)
#   reset      -> J1 A26     -> CAM_RST0_L      -> U34 lvl-shift -> CAM_RST0 -> pad SPK_EN/GPIO495
#                                                  (CAM_RST0/CAM_RST1 same net via R209/R482 0R, shared)
# sensor_cfg.ini lane_id=[clk,d0,d1,d2,d3] = 5,4,3,-1,-1
export PATH=/sbin:/usr/sbin:$PATH
devmem 0x030028C4 32 0x002C0101
devmem 0x03001104 32 0x04
devmem 0x03001108 32 0x04
devmem 0x0300110C 32 0x04
devmem 0x03001020 32 0x03
echo 495 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio495/direction
echo 0 > /sys/class/gpio/gpio495/value
echo 1 > /sys/class/gpio/gpio495/value
