#include <stdio.h>
#include "NuMicro.h"
#include "system.h"

#include "FreeRTOS.h"
#include "task.h"

void continuous_task(void *para)
{
    while (1) {
        printf("%s\n", (char *) para);
    }
}

void periodic_task(void *para)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1) {
        PH4 ^= 1;
        printf("%s\n", (char *) para);
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(500));
    }
}

int main(void)
{
    system_init();

    printf("Here is Lab Task continuous and periodic task.\n");

    // Continuous Task
    xTaskCreate(continuous_task, "task1", 256, "CT1", 1, NULL);
    xTaskCreate(continuous_task, "task2", 256, "CT2", 1, NULL);
    
    // Periodic Task
    xTaskCreate(periodic_task,   "task3", 256, "PT", 2, NULL);

    /* Start the scheduler. */
    vTaskStartScheduler();

    while (1) { ; }
}
