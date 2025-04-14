#!/bin/sh

make clean
make -j || exit "$?"
make package
exit 0
