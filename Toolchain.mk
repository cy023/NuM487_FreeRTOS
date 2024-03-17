##
# @file   Toolchain.mk
# @author cy023 (cyyang023@gmail.com)
# @date   2024.03.17
# @brief  Makefile for Toolchain setting.

################################################################################
# Build Settings
################################################################################

## MCU Info.
CPU       = -mcpu=cortex-m4
MCU       = 
FPU       = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard

## Warning Options
WARNINGS = -Wall -Werror -Wtype-limits -Wno-unused-function

## Debugging Options
DEBUG = -gdwarf-2

## Optimize Options
OPTIMIZE = -O0

## Libraries Path
LIBS    = 
LIBDIRS = 

################################################################################
# Toolchain
################################################################################
COMPILER_PATH ?= 
CROSS   := $(COMPILER_PATH)arm-none-eabi
CC      := $(CROSS)-gcc
AR      := $(CROSS)-ar
SIZE    := $(CROSS)-size
OBJDUMP := $(CROSS)-objdump
OBJCOPY := $(CROSS)-objcopy
NM      := $(CROSS)-nm

## Common Options for assemble, compile and link.
MCUFLAGS = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

## Compile Options
CFLAGS  = $(MCUFLAGS)
CFLAGS += -std=gnu99 $(WARNINGS) $(DEBUG) $(OPTIMIZE)
CFLAGS += -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections
CFLAGS += -Wa,-a,-ad,-alms=$(@:%.o=%.lst)
CFLAGS += -Wp,-MM,-MP,-MT,$(BUILD_DIR)/$(*F).o,-MF,$(BUILD_DIR)/$(*F).d
CFLAGS += $(C_INCLUDES)

## Assembler Options
ASMFLAGS  = $(MCUFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,$(DEBUG)

## Link Options
LDFLAGS  = $(MCUFLAGS)
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$*.map,--cref -Wl,--gc-sections
LDFLAGS += -T$(LDSCRIPT)
LDFLAGS += -specs=nosys.specs -specs=nano.specs -flto
LDFLAGS += -u _printf_float
LDFLAGS += $(LIBDIRS) $(LIBS)

## Archiver Options
# ARFLAGS = rcs

## Intel Hex file production Options
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

################################################################################
# Build The Project
################################################################################

## Preprocess
$(BUILD_DIR)/%.i: %.c Makefile | $(BUILD_DIR)
	$(CC) -E $(C_INCLUDES) $< -o $@

$(BUILD_DIR)/%.i: %.S Makefile | $(BUILD_DIR)
	$(CC) -E $(C_INCLUDES) $< -o $@

## Compile
$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	$(CC) -c $(ASMFLAGS) $< -o $@

## Link
$(TARGET_HEX:.hex=.elf): $(OBJECTS) $(LIBOBJS) Makefile
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBOBJS) -o $@

## Intel HEX format
$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(OBJCOPY) -O ihex $(HEX_FLASH_FLAGS) $< $@

## Binary format
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(OBJCOPY) -O binary $< $@

## Disassemble
$(BUILD_DIR)/%.lss: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(OBJDUMP) -h -S $< > $@

$(BUILD_DIR)/%.lss: $(BUILD_DIR)/%.o | $(BUILD_DIR)
	$(OBJDUMP) -h -S $< > $@

## Symbol Table
$(BUILD_DIR)/%.sym: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(NM) -n $< > $@

$(BUILD_DIR)/%.sym: $(BUILD_DIR)/%.o | $(BUILD_DIR)
	$(NM) -n $< > $@

## Make Directory
$(BUILD_DIR):
	mkdir $@
