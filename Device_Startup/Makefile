##
# @file   Makefile
# @author cy023 (cyyang023@gmail.com)
# @date   2024.03.17
# @brief  Makefile for ./Device_Startup.

################################################################################
# Targets
################################################################################

## Include Path
C_INCLUDES  = -I.

## C Source Path
C_SOURCES += $(wildcard ./*.c)

# Assembly Source Path
ASM_SOURCES += $(wildcard ./*.S)

################################################################################
# dependencies
################################################################################

-include $(wildcard $(BUILD_DIR)/*.d)
-include ../Module.mk
-include ../Toolchain.mk
