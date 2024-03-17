#include <stdio.h>
#include "NuMicro.h"
#include "system.h"

#include "FreeRTOS.h"
#include "task.h"

void task1()
{
    // TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1) {
        printf("Task1...\n");
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
        printf("Task2...\n");
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
