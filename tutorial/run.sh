#!/bin/bash

mkdir -p ../virtualSSD/EFI/BOOT/
cd ../
make
cp BOOTX64.EFI virtualSSD/EFI/BOOT/
qemu-system-x86_64 -bios OVMF.fd -hda fat:rw:virtualSSD
