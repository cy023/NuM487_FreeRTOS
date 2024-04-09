#include <stdio.h>
#include "NuMicro.h"
#include "system.h"

#include "FreeRTOS.h"
#include "task.h"

volatile uint32_t idle_cnt = 0;

void vApplicationIdleHook(void)
{
    idle_cnt++;
}

void taskfunc(void *para)
{
    while (1) {
        printf("%s\n", (char *) para);
        printf("Idle Task Counter: %ld\n", idle_cnt);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

int main(void)
{
    system_init();

    printf("Here is Lab Task idle task.\n");

    xTaskCreate(taskfunc, "task1", 256, "Task1...", 1, NULL);
    xTaskCreate(taskfunc, "task2", 256, "Task2...", 1, NULL);

    /* Start the scheduler. */
    vTaskStartScheduler();

    while (1) { ; }
}
