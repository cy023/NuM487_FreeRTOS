/*
 * FreeRTOS Kernel V10.0.0
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software. If you wish to use our Amazon
 * FreeRTOS name, please do so in a fair use way that does not cause confusion.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */
#include <stdio.h>
#include "NuMicro.h"
#include "system.h"

#include "FreeRTOS.h"
#include "task.h"

void task1()
{
    // TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1) {
        printf("Task1\n");
        PH4 ^= 1;
        system_delay_ms(100); // blocking delay
        taskYIELD();
        // vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(100UL));
        // vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void task2()
{
    // TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1) {
        printf("Task2\n");
        PH5 ^= 1;
        system_delay_ms(100); // blocking delay
        taskYIELD();
        // vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(150UL));
        // vTaskDelay(pdMS_TO_TICKS(300));
    }
}

int main(void)
{
    system_init();

    xTaskCreate(task1, "task1", 256, NULL, tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(task2, "task2", 256, NULL, tskIDLE_PRIORITY + 2, NULL);

    /* Start the scheduler. */
    vTaskStartScheduler();

    while (1) { ; }
}
