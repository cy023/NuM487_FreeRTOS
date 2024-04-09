#include <stdio.h>
#include "NuMicro.h"
#include "system.h"

#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t task2_handle = NULL;

void task1(void *para)
{
    UBaseType_t task1_priority;
    task1_priority = uxTaskPriorityGet(NULL);

    while (1) {
        PH4 ^= 1;
        printf("%s\n", (char *) para);
        vTaskPrioritySet(task2_handle, task1_priority + 1);
    }
}

void task2(void *para)
{
    UBaseType_t task2_priority;
    task2_priority = uxTaskPriorityGet(NULL);

    while (1) {
        PH5 ^= 1;
        printf("%s\n", (char *) para);
        vTaskPrioritySet(NULL, task2_priority - 2);
    }
}

int main(void)
{
    system_init();

    printf("Here is Lab Task change priority.\n");

    xTaskCreate(task1, "task1", 256, "Task1...", 2, NULL);
    xTaskCreate(task2, "task2", 256, "Task2...", 1, &task2_handle);

    /* Start the scheduler. */
    vTaskStartScheduler();

    while (1) { ; }
}
