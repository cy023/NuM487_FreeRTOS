#include <stdio.h>
#include "NuMicro.h"
#include "system.h"

#include "FreeRTOS.h"
#include "task.h"

// Blocking delay leads to double delay time.
#define NON_BLOCKING_DELAY 1

void task1(void *para)
{
    while (1) {
        PH4 ^= 1;
        printf("%s\n", (char *) para);
#if NON_BLOCKING_DELAY
        vTaskDelay(pdMS_TO_TICKS(500));  // non-blocking delay
#else
        system_delay_ms(500);  // blocking delay
#endif
    }
}

void task2(void *para)
{
    while (1) {
        PH5 ^= 1;
        printf("%s\n", (char *) para);
#if NON_BLOCKING_DELAY
        vTaskDelay(pdMS_TO_TICKS(500));  // non-blocking delay
#else
        system_delay_ms(500);  // blocking delay
#endif
    }
}

int main(void)
{
    system_init();

    printf("Here is Lab Task delay (vTaskDelay).\n");

    xTaskCreate(task1, "task1", 256, "Task1...", 1, NULL);
    xTaskCreate(task2, "task2", 256, "Task2...", 1, NULL);

    /* Start the scheduler. */
    vTaskStartScheduler();

    while (1) { ; }
}
