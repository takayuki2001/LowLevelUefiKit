CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -Wall -Wextra -nostdlib -fno-builtin -fno-stack-protector -mno-red-zone -e EfiMain -I ../ -D __X64

TARGETS = \
	hello_world \
	simple_text_output_protocol \
	simple_text_input_protocol \
	simple_os

EXAMPLE_PATH = ./example/

MAKE_SETUP_ERROR = (echo "\e[31m--- Running 'make setup' will probably fix it\e[m"; exit 1)

.PHONY: all
.PHONY: run
.PHONY: clean

all:
	@echo Target is required.

%.dll: $(EXAMPLE_PATH)%/main.c
	$(CC) $(CFLAGS) $< -o $(<D)/$@ || $(MAKE_SETUP_ERROR)

%.EFI: %.dll
	@echo $< : $@
	objcopy --target=efi-app-x86_64 $(EXAMPLE_PATH)$(basename $<)/$< $(EXAMPLE_PATH)$(basename $@)/$@ \
	|| $(MAKE_SETUP_ERROR)

%.QemuInstall: %.EFI
	@echo $< : $@
	mkdir -p ./virtualSSD/EFI/BOOT/
	cp $(EXAMPLE_PATH)$(basename $<)/$< ./virtualSSD/EFI/BOOT/BOOTX64.EFI
	cp $(EXAMPLE_PATH)$(basename $<)/$< ./BOOTX64.EFI

$(TARGETS): %: %.QemuInstall
	make run

run:
	qemu-system-x86_64 --monitor stdio -bios OVMF.fd -hda fat:rw:virtualSSD \
	|| $(MAKE_SETUP_ERROR)

clean:
	rm -rd ./virtualSSD
	rm $(EXAMPLE_PATH)/*/*.EFI
	rm $(EXAMPLE_PATH)/*/*.dll
	rm *.EFI


TARGET_PACKAGE = make

INSTALLED_MOD = _installed
NOT_NINSTELLED_SIGN = ^un
setup:
	@$(eval TARGET_PACKAGE = mingw-w64)
	-@dpkg-query -l $(TARGET_PACKAGE) | grep $(NOT_NINSTELLED_SIGN) && sudo apt install -y $(TARGET_PACKAGE) && touch .$(TARGET_PACKAGE)$(INSTALLED_MOD)

	@$(eval TARGET_PACKAGE = binutils)
	-@dpkg-query -l $(TARGET_PACKAGE) | grep $(NOT_NINSTELLED_SIGN) && sudo apt install -y $(TARGET_PACKAGE) && touch .$(TARGET_PACKAGE)$(INSTALLED_MOD)

	@$(eval TARGET_PACKAGE = qemu-system-x86)
	-@dpkg-query -l $(TARGET_PACKAGE) | grep $(NOT_NINSTELLED_SIGN) && sudo apt install -y $(TARGET_PACKAGE) && touch .$(TARGET_PACKAGE)$(INSTALLED_MOD)
	
	@$(eval TARGET_PACKAGE = ovmf)
	-@dpkg-query -l $(TARGET_PACKAGE) | grep $(NOT_NINSTELLED_SIGN) && sudo apt install -y $(TARGET_PACKAGE) && touch .$(TARGET_PACKAGE)$(INSTALLED_MOD)
	
unsetup:
	@$(eval TARGET_PACKAGE = ovmf)
	-@test -f .$(TARGET_PACKAGE)$(INSTALLED_MOD) && sudo apt remove -y $(TARGET_PACKAGE) && rm .$(TARGET_PACKAGE)$(INSTALLED_MOD)

	@$(eval TARGET_PACKAGE = qemu-system-x86)
	-@test -f .$(TARGET_PACKAGE)$(INSTALLED_MOD) && sudo apt remove -y $(TARGET_PACKAGE) && rm .$(TARGET_PACKAGE)$(INSTALLED_MOD)

	@$(eval TARGET_PACKAGE = binutils)
	-@test -f .$(TARGET_PACKAGE)$(INSTALLED_MOD) && sudo apt remove -y $(TARGET_PACKAGE) && rm .$(TARGET_PACKAGE)$(INSTALLED_MOD)

	@$(eval TARGET_PACKAGE = mingw-w64)
	-@test -f .$(TARGET_PACKAGE)$(INSTALLED_MOD) && sudo apt remove -y $(TARGET_PACKAGE) && rm .$(TARGET_PACKAGE)$(INSTALLED_MOD)
