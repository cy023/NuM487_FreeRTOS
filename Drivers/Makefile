##
# @file   Makefile
# @author cy023 (cyyang023@gmail.com)
# @date   2024.03.17
# @brief  Makefile for ./Drivers.

################################################################################
# Targets
################################################################################

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
# dependencies
################################################################################

-include $(wildcard $(BUILD_DIR)/*.d)
-include ../Module.mk
-include ../Toolchain.mk
