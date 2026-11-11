#!/bin/sh
# SC2331 sensor init: mclk0 + reset(XGPIOA_15) + IIC1 pinmux
# NOTE: gpio495 is claimed by kernel DTS hog "mute_pin_r" (out lo), sysfs export
# always fails busy. Bypass sysfs: write gpio controller data register directly
# (dw-apb-gpio base 0x3020000, bank XGPIOA, bit15 = 0x8000) to release hw reset.
# NOTE: mclk pad is USB_VBUS_DET (0x030010ac, func 4 = CAM_MCLK0).
# MUST configure rndis FIRST, then switch this pad (see agents-memory/phobos3-usb-rndis-pitfalls.md)
echo "[sensor-init] 1/4 mclk0 pinmux (USB_VBUS_DET pad, func 4=CAM_MCLK0)"
devmem 0x030010ac 32 0x04
echo "[sensor-init] 2/4 reset pinmux (XGPIOA_15)"
devmem 0x03001020 32 0x03
echo "[sensor-init] 3/4 iic1 pinmux"
devmem 0x030010c0 32 0x02
devmem 0x030010c4 32 0x02
echo "[sensor-init] 4/4 release hw reset (gpio DR bit15=1, bypass DTS hog)"
devmem 0x3020000 32 0x8000
echo "[sensor-init] verify i2c (SC2331 @0x30):"
i2cdetect -y 1 2>/dev/null | grep -q " 30 " && echo "[sensor-init] SC2331 detected OK" || echo "[sensor-init] WARN: SC2331 NOT detected"
echo "[sensor-init] done"
