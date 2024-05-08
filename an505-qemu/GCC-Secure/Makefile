BUILD_NAME = an505-qemu
BUILD_PATH = build
CMSIS_PATH = ../Drivers/CMSIS_5

PREFIX = arm-none-eabi-
CC  = $(PREFIX)gcc
AS  = $(PREFIX)gcc -x assembler-with-cpp
LD  = $(PREFIX)ld
GDB = $(PREFIX)gdb
OBJ = $(PREFIX)objdump
NM  = $(PREFIX)nm
RD  = $(PREFIX)readelf
CP  = $(PREFIX)objcopy
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

LINKER_SCRIPT = gcc_arm.ld 

SRC_ASM = startup_ARMCM33.s
# ASM sources
SRC_ASMM = 

SRC_C = \
	 ./main.c \
	 ./system_ARMCM33.c \
	../Core/Src/printf.c \
	../Core/Src/uart.c \
	../Core/Src/semihosting.c 

INCLUDE_FLAGS = \
	-I$(CMSIS_PATH)/Device/ARM/ARMCM33/Include \
	-I$(CMSIS_PATH)/CMSIS/Core/Include \
	-I../Core/Inc 

COMMON_CFLAGS = \
	-mcpu=cortex-m33 \
	-g \
	-gdwarf-2 \
	$(INCLUDE_FLAGS) \
	-nostartfiles -ffreestanding \
	-mthumb

CFLAGS = \
	$(COMMON_CFLAGS) \
	-DARMCM33_DSP_FP_TZ \
	-specs=nano.specs -specs=nosys.specs \
	-ffunction-sections \
	-Wl,--gc-sections \
	-DC_SECURE_CODE

SECURE_LINKER_ARGS = \
	-Xlinker --sort-section=alignment \
	-Xlinker --cmse-implib \
	-Xlinker -Map=$(BUILD_PATH)/$(BUILD_NAME).map

all: $(BUILD_PATH)/$(BUILD_NAME).elf $(BUILD_PATH)/$(BUILD_NAME).hex $(BUILD_PATH)/$(BUILD_NAME).bin

OBJS = $(addprefix $(BUILD_PATH)/,$(notdir $(SRC_C:.c=.o)))
vpath %.c $(sort $(dir $(SRC_C)))
OBJS += $(addprefix $(BUILD_PATH)/,$(notdir $(SRC_ASM:.s=.o)))
vpath %.s $(sort $(dir $(SRC_ASM)))
OBJS += $(addprefix $(BUILD_PATH)/,$(notdir $(SRC_ASMM:.S=.o)))
vpath %.S $(sort $(dir $(SRC_ASMM)))

$(BUILD_PATH)/%.o: %.c | $(BUILD_PATH)
	$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_PATH)/%.o: %.s | $(BUILD_PATH)
	$(AS) $(CFLAGS) -c $^ -o $@
$(BUILD_PATH)/%.o: %.S | $(BUILD_PATH)
	$(AS) $(CFLAGS) -c $^ -o $@

$(BUILD_PATH)/$(BUILD_NAME).elf: $(OBJS)
	$(CC) $(CFLAGS) $(SECURE_LINKER_ARGS) $^ -T$(LINKER_SCRIPT) -o $@
	$(NM) $@ > $(BUILD_PATH)/nm.txt
	$(RD) -a $@ > $(BUILD_PATH)/readelf.txt
	$(OBJ) -D $@ > $(BUILD_PATH)/objdump.txt

$(BUILD_PATH)/%.hex: $(BUILD_PATH)/%.elf | $(BUILD_PATH)
	$(HEX) $< $@
	
$(BUILD_PATH)/%.bin: $(BUILD_PATH)/%.elf | $(BUILD_PATH)
	$(BIN) $< $@	

$(BUILD_PATH):
	mkdir $@

clean:
	rm -R $(BUILD_PATH)

-include $(wildcard $(BUILD_PATH)/*.d)
