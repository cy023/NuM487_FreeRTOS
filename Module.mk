##
# @file   Module.mk
# @author cy023 (cyyang023@gmail.com)
# @date   2024.03.17
# @brief  Makefile for library modules.

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
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))

################################################################################
# User Command
################################################################################

all: $(OBJECTS)
	@echo "==================== SIZE ===================="
	$(SIZE) $(OBJECTS)

macro: $(OBJECTS:.o=.i)

dump: $(OBJECTS:.o=.lss) $(OBJECTS:.o=.sym)

clean:
	-rm -rf $(BUILD_DIR)

.PHONY: all clean macro dump
