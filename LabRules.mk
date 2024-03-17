##
# @file   LabRules.mk
# @author cy023 (cyyang023@gmail.com)
# @date   2024.03.17
# @brief  Makefile for lab rules.

################################################################################
# Targets
################################################################################

## Include Path
IPATH = .

## Build Output Path
BUILD_DIR = build

## Build Reference Path
VPATH = $(sort $(dir $(C_SOURCES)))

## Object Files
OBJECTS  = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o))) 
LIBOBJS  = $(wildcard $(ROOT_PATH)/Device_Startup/build/*.o)
LIBOBJS += $(wildcard $(ROOT_PATH)/Drivers/build/*.o)
LIBOBJS += $(wildcard $(ROOT_PATH)/Middleware/build/*.o)

## Target File
TARGET_HEX = $(BUILD_DIR)/$(TARGET).hex

# Module Path
MODULE_DIRS  = $(ROOT_PATH)/Device_Startup
MODULE_DIRS += $(ROOT_PATH)/Drivers
MODULE_DIRS += $(ROOT_PATH)/Middleware

################################################################################
# User Command
################################################################################

all: lib $(OBJECTS)
	@make $(TARGET_HEX)
	@echo "==================== SIZE ===================="
	$(SIZE) $(OBJECTS)
	$(SIZE) $(TARGET_HEX)

lib: $(LIBOBJS)
	$(foreach dir,$(MODULE_DIRS),make -C $(dir) CONFIG_PATH=$(CONFIG_DIR);)

macro:
	$(foreach dir,$(MODULE_DIRS),make -C $(dir) macro CONFIG_PATH=$(CONFIG_DIR);)
	@make $(OBJECTS:.o=.i)

dump:
	$(foreach dir,$(MODULE_DIRS),make -C $(dir) dump CONFIG_PATH=$(CONFIG_DIR);)
	@make $(OBJECTS:.o=.lss) $(OBJECTS:.o=.sym)

clean:
	$(foreach dir,$(MODULE_DIRS),make -C $(dir) clean;)
	-rm -rf $(BUILD_DIR)

.PHONY: all clean lib macro dump
