#!/bin/sh
#
# To use, hold down the boot (BO) button when you plug 
# the board in to enter bootloader mode.
#
# Note: if you've built your own DFU file, this requires that
# you copy and rename the firmware.dfu from the build directory
# to your local directory.

DFU_FILE=WEACT_STM32H562_20250702-v1.26.0-preview.dfu

dfu-util --alt 0 -D $DFU_FILE

echo "complete."
