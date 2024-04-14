##
# @file   Makefile
# @author cy023 (cyyang023@gmail.com)
# @date   2024.03.17
# @brief  Makefile for lab.

################################################################################
# Targets
################################################################################

## Target
TARGET = main

## Lab directory
LAB_DIR = Core/Lab_Task_continuous_and_periodic_task

## Root Path
ROOT_PATH = ../..

## Config Include Path
CONFIG_DIR = ../$(LAB_DIR)

## Include Path
C_INCLUDES  = -I.
C_INCLUDES += -I$(ROOT_PATH)/$(LAB_DIR)
C_INCLUDES += -I$(ROOT_PATH)/Device_Startup
C_INCLUDES += -I$(ROOT_PATH)/Drivers/HAL
C_INCLUDES += -I$(ROOT_PATH)/Drivers/CMSIS
C_INCLUDES += -I$(ROOT_PATH)/Drivers/Library/Device/Nuvoton_M480/Include
C_INCLUDES += -I$(ROOT_PATH)/Drivers/Library/StdDriver/inc
C_INCLUDES += -I$(ROOT_PATH)/Middleware/FreeRTOS-KernelV11.0.1/include
C_INCLUDES += -I$(ROOT_PATH)/Middleware/FreeRTOS-KernelV11.0.1/portable/GCC/ARM_CM4F

## C Source Path
C_SOURCES += $(wildcard ./*.c)

### Linker script
LDSCRIPT = $(ROOT_PATH)/Device_Startup/gcc_arm.ld

################################################################################
# dependencies
################################################################################

-include $(wildcard $(BUILD_DIR)/*.d)
-include $(ROOT_PATH)/LabRules.mk
-include $(ROOT_PATH)/Toolchain.mk
