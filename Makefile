CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -Wall -Wextra -nostdlib -fno-builtin -fno-stack-protector -mno-red-zone -e EfiMain -D __X64

all: BOOTX64.EFI

BOOTX64.dll: main.c
	$(CC) $(CFLAGS) $< -o $@

BOOTX64.EFI: BOOTX64.dll
	objcopy --target=efi-app-x86_64 $< $@

clean:
	rm -f BOOTX64.EFI
	rm -f BOOTX64.dll