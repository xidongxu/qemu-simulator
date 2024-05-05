BINARY = an505-qemu
BINARY_LIB_S = cmse_import.o
MACHINE_NAME := mps2-an505
BUILD_PATH = build
CMSIS_PATH = ../Drivers/CMSIS_5

CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
GDB = $(CROSS_COMPILE)gdb
OBJ = $(CROSS_COMPILE)objdump
NM = $(CROSS_COMPILE)nm
READELF = $(CROSS_COMPILE)readelf
CP = $(CROSS_COMPILE)objcopy
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

# Must match the same value in the NS linker script where the vector table is.
TZ_VTOR_TABLE_ADDR = 0x00200000
LINKER_SCRIPT = gcc_arm.ld 

SRC_ASM = startup_ARMCM33.s

SRC_C = \
	system_ARMCM33.c \
	main.c \
	../Core/Src/logPrint.c \
	../Core/Src/uart.c 

INCLUDE_FLAGS = \
	-I$(CMSIS_PATH)/Device/ARM/ARMCM33/Include \
	-I$(CMSIS_PATH)/CMSIS/Core/Include \
	-I../Core/Inc 

COMMON_CFLAGS = \
	-mcpu=cortex-m33 \
	-g \
	$(INCLUDE_FLAGS) \
	-nostartfiles -ffreestanding \
	-mthumb

CFLAGS = \
	$(COMMON_CFLAGS) \
	-DARMCM33_DSP_FP_TZ \
	-mcmse \
	-DTZ_VTOR_TABLE_ADDR=$(TZ_VTOR_TABLE_ADDR) \
	-specs=nano.specs -specs=nosys.specs \
	-ffunction-sections \
	-Wl,--gc-sections \
	-DC_SECURE_CODE

SECURE_LINKER_ARGS = \
	-Xlinker --sort-section=alignment \
	-Xlinker --cmse-implib \
	-Xlinker --out-implib=$(BUILD_PATH)/$(BINARY_LIB_S) \
	-Xlinker -Map=$(BUILD_PATH)/$(BINARY).map

all: $(BUILD_PATH)/$(BINARY).elf $(BUILD_PATH)/$(BINARY).hex $(BUILD_PATH)/$(BINARY).bin

OBJS = $(addprefix $(BUILD_PATH)/,$(notdir $(SRC_C:.c=.o)))
vpath %.c $(sort $(dir $(SRC_C)))
OBJS += $(addprefix $(BUILD_PATH)/,$(notdir $(SRC_ASM:.s=.o)))
vpath %.s $(sort $(dir $(SRC_ASM)))

$(BUILD_PATH)/%.o: %.c | $(BUILD_PATH)
	$(CC) $(CFLAGS) -o $@ -c $<
$(BUILD_PATH)/%.o: %.s | $(BUILD_PATH)
	$(CC) $(CFLAGS) -c $^ -o $@

# Generate two separate images (one for Non-Secure and another for Secure) with
# different linker scripts (as they will have different addresses to locate the code).
# This is to make sure that there is no clash with the symbols.
$(BUILD_PATH)/$(BINARY).elf: $(OBJS)
	$(CC) $(CFLAGS) $(SECURE_LINKER_ARGS) $^ -T$(LINKER_SCRIPT) -o $@
	$(NM) $@ > $(BUILD_PATH)/nm.txt
	$(OBJ) -D $@ > $(BUILD_PATH)/objdump.txt
	$(READELF) -a $@ > $(BUILD_PATH)/readelf.txt

$(BUILD_PATH)/%.hex: $(BUILD_PATH)/%.elf | $(BUILD_PATH)
	$(HEX) $< $@
	
$(BUILD_PATH)/%.bin: $(BUILD_PATH)/%.elf | $(BUILD_PATH)
	$(BIN) $< $@	

$(BUILD_PATH):
	mkdir $@

clean:
	rm -R $(BUILD_PATH)

-include $(wildcard $(BUILD_PATH)/*.d)
