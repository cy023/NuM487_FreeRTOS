#include <stdio.h>
#include "NuMicro.h"
#include "system.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#define ONESHOT_TIMER_PERIOD    pdMS_TO_TICKS(3333)
#define AUTORELOAD_TIMER_PERIOD pdMS_TO_TICKS(500)

TimerHandle_t one_shot_timer, auto_reload_timer;

void timer_callback(TimerHandle_t xTimer)
{
    TickType_t tick_now;
    uint32_t execution_count;

    execution_count = (uint32_t) pvTimerGetTimerID(xTimer);
    execution_count++;
    vTimerSetTimerID(xTimer, (void *) execution_count);

    tick_now = xTaskGetTickCount();

    if (xTimer == one_shot_timer) {
        printf("One-Shot Timer callback: %d\n", tick_now);
    } else if (xTimer == auto_reload_timer) {
        printf("Auto-Reload Timer callback: %d\n", tick_now);

        if (execution_count == 5) {
            xTimerStop(xTimer, 0);
        }
    }
}

int main(void)
{
    BaseType_t status1, status2;

    system_init();

    printf("Here is Lab Software Timer Timer ID.\n");

    one_shot_timer = xTimerCreate("One-Shot", ONESHOT_TIMER_PERIOD, pdFALSE, 0,
                                  timer_callback);

    auto_reload_timer = xTimerCreate("Auto-Reload", AUTORELOAD_TIMER_PERIOD,
                                     pdTRUE, 0, timer_callback);

    if (one_shot_timer == NULL || auto_reload_timer == NULL) {
        printf("Create timer fail.\n");
        return 0;
    }

    status1 = xTimerStart(one_shot_timer, 0);
    status2 = xTimerStart(auto_reload_timer, 0);
    if (status1 != pdPASS || status2 != pdPASS) {
        printf("Start timer fail.\n");
        return 0;
    }

    /* Start the scheduler. */
    vTaskStartScheduler();

    while (1) { ; }
}
