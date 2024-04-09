#include <stdio.h>
#include "NuMicro.h"
#include "system.h"

#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t task2_handle = NULL;

// forward declaration
void task2(void *para);

void task1(void *para)
{
    while (1) {
        PH4 ^= 1;
        printf("%s\n", (char *) para);

        // task 2 priority is higher than task 1, so it will preempt task1.
        xTaskCreate(task2, "task2", 256, "Task2...", 2, &task2_handle);

        // After deleting task2, it returns to the place it just preempted.
        printf("[In task1]: task2 have been deleted.\n");

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void task2(void *para)
{
    PH5 ^= 1;
    printf("%s\n", (char *) para);
    vTaskDelete(task2_handle);
    printf("[In task2]: task2 have been deleted.\n");  // Will not execute here.
}

int main(void)
{
    system_init();

    printf("Here is Lab Task delete task.\n");

    xTaskCreate(task1, "task1", 256, "Task1...", 1, NULL);

    /* Start the scheduler. */
    vTaskStartScheduler();

    while (1) { ; }
}
