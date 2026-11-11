#!/bin/sh
export PATH=/sbin:/usr/sbin:$PATH
devmem 0x030028C0 32 0x002C0101
devmem 0x03001104 32 0x04
devmem 0x03001108 32 0x04
devmem 0x03001110 32 0x04
devmem 0x03001020 32 0x03
echo 495 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio495/direction
echo 0 > /sys/class/gpio/gpio495/value
echo 1 > /sys/class/gpio/gpio495/value
