##
# @file   Makefile
# @author cy023@MVMC-Lab (cyyang023@gmail.com)
# @date   2022.09.17
# @brief  Makefile for NuM487 project.

## Include Path
C_INCLUDES  = -I.
C_INCLUDES += -I./HAL
C_INCLUDES += -I./CMSIS
C_INCLUDES += -I./Library/Device/Nuvoton_M480/Include
C_INCLUDES += -I./Library/StdDriver/inc

## C Source Path
C_SOURCES += $(wildcard ./HAL/*.c)
C_SOURCES += $(wildcard ./Library/Device/Nuvoton_M480/Source/*.c)
# C_SOURCES += $(wildcard ./Library/StdDriver/src/*.c)
C_SOURCES += ./Library/StdDriver/src/sys.c
C_SOURCES += ./Library/StdDriver/src/uart.c
C_SOURCES += ./Library/StdDriver/src/gpio.c
C_SOURCES += ./Library/StdDriver/src/retarget.c
C_SOURCES += ./Library/StdDriver/src/clk.c

################################################################################
# Project Architecture
################################################################################

## Include Path
IPATH = .

## Build Output Path
BUILD_DIR = build

## Build Reference Path
VPATH  = $(sort $(dir $(C_SOURCES)))

## Object Files
OBJECTS  = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o))) 

################################################################################
# User Command
################################################################################

all: $(OBJECTS)
	@echo "========== SIZE =========="
	$(SIZE) $^

macro: $(OBJECTS:.o=.i)

# dump: $(BUILD_DIR)/$(TARGET).lss $(TESTOBJ:.o=.lss) $(BUILD_DIR)/$(TARGET).sym $(TESTOBJ:.o=.sym)

# size: $(TARGET_FILE)
# 	$(SIZE) $(TARGET_FILE)

clean:
	-rm -rf $(BUILD_DIR)

# upload:
# 	serprog prog -p $(COMPORT) -f build/$(UPLOAD_HEX).hex

# terminal:
# 	putty -serial $(COMPORT) -sercfg 38400,1,N,N

# systeminfo:
# 	@uname -a
# 	@$(CC) --version

# .PHONY: all test macro dump size systeminfo clean upload terminal
.PHONY: all clean

################################################################################
# dependencies
################################################################################

-include $(wildcard $(BUILD_DIR)/*.d)
-include ../Toolchain.mk
