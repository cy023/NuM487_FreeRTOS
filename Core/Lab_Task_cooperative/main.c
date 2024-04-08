#include <stdio.h>
#include "NuMicro.h"
#include "system.h"

#include "FreeRTOS.h"
#include "task.h"

void task1(void *para)
{
    while (1) {
        PH4 ^= 1;
        printf("%s\n", (char *) para);
        taskYIELD();
    }
}

void task2(void *para)
{
    while (1) {
        PH5 ^= 1;
        printf("%s\n", (char *) para);
        taskYIELD();
    }
}

int main(void)
{
    system_init();

    printf("Here is Lab Task cooperative.\n");

    xTaskCreate(task1, "task1", 256, "Task1...", 1, NULL);
    xTaskCreate(task2, "task2", 256, "Task2...", 1, NULL);

    /* Start the scheduler. */
    vTaskStartScheduler();

    while (1) { ; }
}
