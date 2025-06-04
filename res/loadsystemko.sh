#!/bin/sh
${CVI_SHOPTS}
#
# Start to insert kernel modules
#
insmod ./ko/cv184x_osal.ko
insmod ./ko/cv184x_base.ko
insmod ./ko/cv184x_sys.ko
insmod ./ko/cv184x_mipi_rx.ko
insmod ./ko/cv184x_vi.ko
insmod ./ko/cv184x_vpss.ko
insmod ./ko/cv184x_vc_drv.ko
insmod ./ko/cv184x_snsr_i2c.ko

#devmem 0x30010f0 8 0x2
#devmem 0x30010f4 8 0x2
#devmem 0xa090004 32 0x4
#devmem 0xa090004 32 0x0
devmem 0x3001014 8 0x0
devmem 0x3001018 8 0x0
devmem 0x3001000 8 0x0
dmesg -n 4

echo 3 > /proc/sys/vm/drop_caches
mdev -s

#usb hub control
#/etc/uhubon.sh host

exit $?
