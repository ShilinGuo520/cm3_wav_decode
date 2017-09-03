# MCU name and submodel
MCU      = cortex-m3
SUBMDL   = stm32f103

TARGET = application

# toolchain (using code sourcery now)
THUMB    = -mthumb

#--------------compile tools-------------------
CROSS_COMPILE ?= arm-none-eabi-
CC       := $(CROSS_COMPILE)gcc
LD       := $(CROSS_COMPILE)ld -v
AS       := $(CROSS_COMPILE)gcc
AR		 := $(CROSS_COMPILE)ar
OBJCOPY  := $(CROSS_COMPILE)objcopy
OBJDUMP  := $(CROSS_COMPILE)objdump


INC = -I./inc
CFLAGS =$(THUMB) -O2 -g3 -gdwarf-2 -nostdlib -ffunction-sections -fdata-sections -Wl,--gc-sections -fno-builtin $(INC)
ASFLAGS = -x assembler-with-cpp
LDFLAGS = -T./cm3/link_cmd.ld -Mmap > map.txt
ARFLAGS = -rv


ALL_LIB = libcommon.a
ALL_LIB += libdriver.a
ALL_LIB += libglib.a
ALL_LIB += libfs.a
ALL_LIB += libgcc.lib

ALL_SRC = start_up.o $(ALL_LIB)


$(TARGET):$(ALL_SRC)
	$(LD) $(LDFLAGS) $(ALL_SRC) --output $(TARGET).elf
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin
	$(OBJDUMP) -h -S -D $(TARGET).elf > objdump.txt

libglib.a:
	$(MAKE) -C glib

libcommon.a:
	$(MAKE) -C common

libdriver.a:
	$(MAKE) -C driver

libfs.a:
	$(MAKE) -C fs

start_up.o:
	$(AS) $(ASFLAGS) -o start_up.o -c ./cm3/start_up.S


clean:
	$(MAKE) clean -C common
	$(MAKE)	clean -C driver
	$(MAKE) clean -C glib
	$(MAKE) clean -C fs
	rm -f *.o *.a *.elf *.bin *.txt

