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

    printf("Here is Lab Task preemptive.\n");

    xTaskCreate(taskfunc, "task1", 256, "Task1...", 1, NULL);
    xTaskCreate(taskfunc, "task2", 256, "Task2...", 1, NULL);

    /* Start the scheduler. */
    vTaskStartScheduler();

    while (1) { ; }
}
