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
UPLOAD_LAB ?= Core/Lab_Software_Timer_reset
UPLOAD_HEX ?= main

################################################################################
# Targets
################################################################################

# LAB_DIRS  = Core/Lab_Task_LED
# LAB_DIRS += Core/Lab_Task_preemptive
# LAB_DIRS += Core/Lab_Task_cooperative
# LAB_DIRS += Core/Lab_Task_starved
# LAB_DIRS += Core/Lab_Task_delay
# LAB_DIRS += Core/Lab_Task_periodic
# LAB_DIRS += Core/Lab_Task_idle_task
# LAB_DIRS += Core/Lab_Task_change_priority
# LAB_DIRS += Core/Lab_Task_delete_task
# LAB_DIRS += Core/Lab_Task_continuous_and_periodic_task
# LAB_DIRS += Core/Lab_Queue_blocking_on_reads
# LAB_DIRS += Core/Lab_Queue_blocking_on_writes
# LAB_DIRS += Core/Lab_Queue_queue_set
# LAB_DIRS += Core/Lab_Software_Timer_oneshot_and_autoreload
# LAB_DIRS += Core/Lab_Software_Timer_timer_id
LAB_DIRS += Core/Lab_Software_Timer_reset

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
