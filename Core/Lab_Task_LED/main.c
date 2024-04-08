#include <stdio.h>
#include "NuMicro.h"
#include "system.h"

#include "FreeRTOS.h"
#include "task.h"

void task1()
{
    while (1) {
        PH4 ^= 1;
        printf("Task1...\n");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void task2()
{
    while (1) {
        PH5 ^= 1;
        printf("Task2...\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void)
{
    system_init();

    printf("Here is Lab Task LED.\n");

    xTaskCreate(task1, "task1", 256, NULL, 1, NULL);
    xTaskCreate(task2, "task2", 256, NULL, 1, NULL);

    /* Start the scheduler. */
    vTaskStartScheduler();

    while (1) { ; }
}
