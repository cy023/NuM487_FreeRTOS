##
# @file   Makefile
# @author cy023 (cyyang023@gmail.com)
# @date   2024.03.17
# @brief  Makefile for NuM487_FreeRTOS project.

################################################################################
# User Settings
################################################################################

# Upload Info.
COMPORT    ?= /dev/ttyACM0
UPLOAD_LAB ?= Core/Lab02
UPLOAD_HEX ?= main

################################################################################
# Targets
################################################################################

LAB_DIRS  = Core/Lab01
LAB_DIRS += Core/Lab02

################################################################################
# User Command
################################################################################

lab:
	$(foreach dir,$(LAB_DIRS),make -C $(dir);)

macro:
	$(foreach dir,$(LAB_DIRS),make -C $(dir) macro;)

dump:
	$(foreach dir,$(LAB_DIRS),make -C $(dir) dump;)

clean:
	$(foreach dir,$(LAB_DIRS),make -C $(dir) clean;)

upload:
	serprog prog -p $(COMPORT) -f $(UPLOAD_LAB)/build/$(UPLOAD_HEX).hex

terminal:
	putty -serial $(COMPORT) -sercfg 38400,1,N,N

systeminfo:
	@uname -a
	@$(CC) --version

.PHONY: lab clean macro dump upload terminal systeminfo
