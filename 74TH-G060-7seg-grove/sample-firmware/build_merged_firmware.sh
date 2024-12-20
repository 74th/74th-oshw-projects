#!/bin/bash
set -xe
pio pkg exec -p tool-esptoolpy esptool.py -- --chip esp32 merge_bin \
  -o firmware.bin \
  --flash_mode dio \
  --flash_freq 80m \
  --flash_size 8MB \
  0x0000 .pio/build/m5stack-atom/bootloader.bin \
  0x8000 .pio/build/m5stack-atom/partitions.bin \
  0xe000 ~/.platformio/packages/framework-arduinoespressif32/tools/partitions/boot_app0.bin \
  0x10000 .pio/build/m5stack-atom/firmware.bin