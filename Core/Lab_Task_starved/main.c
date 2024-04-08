#include <stdio.h>
#include "NuMicro.h"
#include "system.h"

#include "FreeRTOS.h"
#include "task.h"

void taskfunc(void *para)
{
    while (1) {
        printf("%s\n", (char *) para);
    }
}

int main(void)
{
    system_init();

    printf("Here is Lab Task starved.\n");

    // Task1 starved ...
    xTaskCreate(taskfunc, "task1", 256, "Task1...", 1, NULL); // lower priority
    xTaskCreate(taskfunc, "task2", 256, "Task2...", 2, NULL); // higher priority

    /* Start the scheduler. */
    vTaskStartScheduler();

    while (1) { ; }
}
