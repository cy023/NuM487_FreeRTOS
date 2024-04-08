/*
 * FreeRTOS Kernel V11.0.1
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/******************************************************************************/
/* Hardware description related definitions. **********************************/
/******************************************************************************/
#include <stdint.h>
extern uint32_t SystemCoreClock;

#define configCPU_CLOCK_HZ                          (SystemCoreClock)

/******************************************************************************/
/* Scheduling behaviour related definitions. **********************************/
/******************************************************************************/
#define configTICK_RATE_HZ                          ((portTickType) 100)
#define configUSE_PREEMPTION                        1
#define configUSE_TIME_SLICING                      1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION     0
#define configUSE_TICKLESS_IDLE                     0
#define configMAX_PRIORITIES                        (5)
#define configMINIMAL_STACK_SIZE                    ((unsigned short) 50)
#define configMAX_TASK_NAME_LEN                     (10)
#define configTICK_TYPE_WIDTH_IN_BITS               TICK_TYPE_WIDTH_16_BITS
// #define configUSE_16_BIT_TICKS                      0
#define configIDLE_SHOULD_YIELD                     1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES       1U
#define configQUEUE_REGISTRY_SIZE                   8
#define configENABLE_BACKWARD_COMPATIBILITY         1
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS     0
#define configSTACK_DEPTH_TYPE                      size_t
#define configMESSAGE_BUFFER_LENGTH_TYPE            size_t
#define configUSE_NEWLIB_REENTRANT                  0

/******************************************************************************/
/* Software timer related definitions. ****************************************/
/******************************************************************************/
#define configUSE_TIMERS                            1
#define configTIMER_TASK_PRIORITY                   (2)
#define configTIMER_QUEUE_LENGTH                    (10)
#define configTIMER_TASK_STACK_DEPTH                (configMINIMAL_STACK_SIZE * 2)

/******************************************************************************/
/* Co-routine related definitions. ********************************************/
/******************************************************************************/
#define configUSE_CO_ROUTINES                       0
#define configMAX_CO_ROUTINE_PRIORITIES             (2)

/******************************************************************************/
/* Memory allocation related definitions. *************************************/
/******************************************************************************/
#define configSUPPORT_STATIC_ALLOCATION             0
#define configSUPPORT_DYNAMIC_ALLOCATION            1
#define configTOTAL_HEAP_SIZE                       ((size_t) (8 * 1024))
#define configAPPLICATION_ALLOCATED_HEAP            0
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP   0
#define configUSE_MINI_LIST_ITEM                    1
#define configENABLE_HEAP_PROTECTOR                 0
#define configKERNEL_PROVIDED_STATIC_MEMORY         0
#define configHEAP_CLEAR_MEMORY_ON_FREE             0

/******************************************************************************/
/* Interrupt nesting behaviour configuration. *********************************/
/******************************************************************************/
/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
/* __NVIC_PRIO_BITS will be specified when CMSIS is being used. */
#define configPRIO_BITS     4
#else
#define configPRIO_BITS     4   /* 15 priority levels */
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY 0xF

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5

/* configKERNEL_INTERRUPT_PRIORITY sets the priority of the tick and context
 * switch performing interrupts.  The default value is set to the highest
 * interrupt priority (0). */
#define configKERNEL_INTERRUPT_PRIORITY \
    (configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))

/* configMAX_SYSCALL_INTERRUPT_PRIORITY sets the interrupt priority above which
 * FreeRTOS API calls must not be made.  Interrupts above this priority are
 * never disabled, so never delayed by RTOS activity.  The default value is set
 * to the highest interrupt priority (0). */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY \
    (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))

/* Another name for configMAX_SYSCALL_INTERRUPT_PRIORITY - the name used depends
 * on the FreeRTOS port. */
#define configMAX_API_CALL_INTERRUPT_PRIORITY   0U

/******************************************************************************/
/* Hook and callback function related definitions. ****************************/
/******************************************************************************/
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configUSE_MALLOC_FAILED_HOOK            0
#define configUSE_DAEMON_TASK_STARTUP_HOOK      0
#define configCHECK_FOR_STACK_OVERFLOW          0
#define configUSE_SB_COMPLETED_CALLBACK         0

/******************************************************************************/
/* Run time and task stats gathering related definitions. *********************/
/******************************************************************************/
#define configGENERATE_RUN_TIME_STATS           0
#define configUSE_TRACE_FACILITY                1
#define configUSE_STATS_FORMATTING_FUNCTIONS    0
#define configKERNEL_PROVIDED_STATIC_MEMORY     0

/******************************************************************************/
/* Definitions that include or exclude functionality. *************************/
/******************************************************************************/
#define configUSE_TASK_NOTIFICATIONS            1
#define configUSE_MUTEXES                       1
#define configUSE_RECURSIVE_MUTEXES             1
#define configUSE_COUNTING_SEMAPHORES           1
#define configUSE_QUEUE_SETS                    1
#define configUSE_APPLICATION_TASK_TAG          0
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_uxTaskGetStackHighWaterMark     0
#define INCLUDE_xTaskGetIdleTaskHandle          0
#define INCLUDE_eTaskGetState                   0
#define INCLUDE_xTimerPendFunctionCall          0
#define INCLUDE_xTaskAbortDelay                 0
#define INCLUDE_xTaskGetHandle                  0
#define INCLUDE_xTaskResumeFromISR              1

/******************************************************************************/
/* Debugging assistance. ******************************************************/
/******************************************************************************/

/* configASSERT() has the same semantics as the standard C assert().  It can
 * either be defined to take an action when the assertion fails, or not defined
 * at all (i.e. comment out or delete the definitions) to completely remove
 * assertions.  configASSERT() can be defined to anything you want, for example
 * you can call a function if an assert fails that passes the filename and line
 * number of the failing assert (for example, "vAssertCalled( __FILE__, __LINE__ )"
 * or it can simple disable interrupts and sit in a loop to halt all execution
 * on the failing line for viewing in a debugger. */
#define configASSERT( x )         \
    if( ( x ) == 0 )              \
    {                             \
        taskDISABLE_INTERRUPTS(); \
        for( ; ; )                \
        ;                         \
    }

/******************************************************************************/
/* Definitions that map the FreeRTOS port interrupt handlers. *****************/
/******************************************************************************/
#define vPortSVCHandler     SVC_Handler
#define xPortPendSVHandler  PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */
