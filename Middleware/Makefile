##
# @file   Makefile
# @author cy023 (cyyang023@gmail.com)
# @date   2024.03.17
# @brief  Makefile for ./Middleware.

################################################################################
# Targets
################################################################################

## Include Path
C_INCLUDES  = -I./FreeRTOS-KernelV11.0.1/include
C_INCLUDES += -I./FreeRTOS-KernelV11.0.1/portable/GCC/ARM_CM4F
C_INCLUDES += -I$(CONFIG_PATH)

## C Source Path
C_SOURCES  = $(wildcard ./FreeRTOS-KernelV11.0.1/*.c)
C_SOURCES += ./FreeRTOS-KernelV11.0.1/portable/GCC/ARM_CM4F/port.c
C_SOURCES += ./FreeRTOS-KernelV11.0.1/portable/MemMang/heap_4.c

################################################################################
# dependencies
################################################################################

-include $(wildcard $(BUILD_DIR)/*.d)
-include ../Module.mk
-include ../Toolchain.mk
