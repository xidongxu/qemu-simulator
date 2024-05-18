BUILD_NAME = an505-qemu
BUILD_PATH = build
CMSIS_PATH = ../Drivers/CMSIS_5

# debug build
DEBUG = 1
# optimization
OPT = -Og

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

# cpu
CPU = -mcpu=cortex-m33

# fpu
FPU = -mfpu=fpv5-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# AS defines
AS_DEF = 

# asm sources
ASM_SRC = \
	startup_ARMCM33.s \
	../../../libutils/fault-dump/cpu/cortex-m33/fault-gcc.s 

# ASM sources
ASMM_SRC = 

# AS includes
AS_INC = 

# C defines
C_DEF = \
	-DARMCM33_DSP_FP 

# C sources
C_SRC = \
	 ./main.c \
	 ./system_ARMCM33.c \
	../Core/Src/printf.c \
	../Core/Src/uart.c \
	../Core/Src/semihosting.c \
	../../../libutils/fault-dump/src/fault-dump.c 

# C includes
C_INC = \
	-I$(CMSIS_PATH)/Device/ARM/ARMCM33/Include \
	-I$(CMSIS_PATH)/CMSIS/Core/Include \
	-I../Core/Inc \
	-I../../../libutils/fault-dump/inc \
	-I../../../libutils/fault-dump/cpu/cortex-m33  

# as compile flags
ASFLAGS = \
	$(MCU) \
	$(AS_DEF) \
	$(AS_INC) \
	$(OPT) \
	-Wall \
	-specs=nosys.specs \
	-fdata-sections \
	-ffunction-sections \
	-fno-exceptions 

# c compile flags
CFLAGS = \
	$(MCU) \
	$(C_DEF) \
	$(C_INC) \
	$(OPT) \
	-Wall \
	-mthumb \
	-specs=nosys.specs \
	-fdata-sections \
	-ffunction-sections \
	-fno-exceptions 

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

# link script
LINKER_SCRIPT = gcc_arm.ld 
LIBS = 
LIBDIR = 

# linker compile flags
LDFLAGS = \
	$(MCU) --specs=nosys.specs -T$(LINKER_SCRIPT) \
	$(LIBDIR) \
	$(LIBS) \
	-Wl,-Map=$(BUILD_PATH)/$(BUILD_NAME).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_PATH)/$(BUILD_NAME).elf $(BUILD_PATH)/$(BUILD_NAME).hex $(BUILD_PATH)/$(BUILD_NAME).bin

# list of objects
OBJS = $(addprefix $(BUILD_PATH)/,$(notdir $(C_SRC:.c=.o)))
vpath %.c $(sort $(dir $(C_SRC)))
# list of ASM program objects
OBJS += $(addprefix $(BUILD_PATH)/,$(notdir $(ASM_SRC:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SRC)))
OBJS += $(addprefix $(BUILD_PATH)/,$(notdir $(ASMM_SRC:.S=.o)))
vpath %.S $(sort $(dir $(ASMM_SRC)))

$(BUILD_PATH)/%.o: %.c | $(BUILD_PATH)
	$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_PATH)/%.o: %.s | $(BUILD_PATH)
	$(AS) $(CFLAGS) -c $^ -o $@
$(BUILD_PATH)/%.o: %.S | $(BUILD_PATH)
	$(AS) $(CFLAGS) -c $^ -o $@

$(BUILD_PATH)/$(BUILD_NAME).elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@
	$(NM) $@ > $(BUILD_PATH)/nm.txt
	$(RD) -a $@ > $(BUILD_PATH)/readelf.txt
	$(OBJ) -D -S $@ > $(BUILD_PATH)/objdump.txt

$(BUILD_PATH)/%.hex: $(BUILD_PATH)/%.elf | $(BUILD_PATH)
	$(HEX) $< $@
	
$(BUILD_PATH)/%.bin: $(BUILD_PATH)/%.elf | $(BUILD_PATH)
	$(BIN) $< $@	

$(BUILD_PATH):
	mkdir $@

# clean up
clean:
ifeq ($(OS),Windows_NT)
	del $(BUILD_PATH)\*.d
	del $(BUILD_PATH)\*.o
else
	rm -f $(BUILD_PATH)/*.d
	rm -f $(BUILD_PATH)/*.o
endif

# start qemu for debug
debug:
	.\an505-start.bat

# dependencies
-include $(wildcard $(BUILD_PATH)/*.d)
