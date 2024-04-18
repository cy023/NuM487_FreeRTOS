#include <stdio.h>
#include "NuMicro.h"
#include "system.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#define ONESHOT_TIMER_PERIOD    pdMS_TO_TICKS(3333)
#define AUTORELOAD_TIMER_PERIOD pdMS_TO_TICKS(500)

TimerHandle_t one_shot_timer, auto_reload_timer;

void one_shot_timer_callback(TimerHandle_t xTimer)
{
    TickType_t tick_now = xTaskGetTickCount();
    printf("One-Shot Timer callback: %d\n", tick_now);
}

void auto_reload_timer_callback(TimerHandle_t xTimer)
{
    TickType_t tick_now = xTaskGetTickCount();
    // The setting `configTICK_RATE_HZ = 100` is in the FreeRTOSConfig.h
    // It's 10ms/Tick.
    printf("Auto-Reload Timer callback: %d\n", tick_now);
}

int main(void)
{
    BaseType_t status1, status2;

    system_init();

    printf("Here is Lab Software Timer one-shot and auto-reload.\n");

    one_shot_timer = xTimerCreate("One-Shot", ONESHOT_TIMER_PERIOD, pdFALSE, 0,
                                  one_shot_timer_callback);

    auto_reload_timer = xTimerCreate("Auto-Reload", AUTORELOAD_TIMER_PERIOD,
                                     pdTRUE, 0, auto_reload_timer_callback);

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
