#include <stdio.h>
#include "NuMicro.h"
#include "system.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#define BLACKLIGHT_TIMER_PERIOD pdMS_TO_TICKS(5000)

TimerHandle_t blacklight_timer;

BaseType_t simulated_blacklightOn = pdFALSE;

uint8_t detect_press(void)
{
    return !PE5;
}

void blacklight_timer_callback(TimerHandle_t xTimer)
{
    TickType_t tick_now = xTaskGetTickCount();
    simulated_blacklightOn = pdFALSE;
    printf("Timer expired, turning blacklight OFF at time\t%d\n", tick_now);
}

void detect_task(void *para)
{
    TickType_t tick_now;
    while (1) {
        PH4 ^= 1;
        if (detect_press()) {
            tick_now = xTaskGetTickCount();
            if (simulated_blacklightOn == pdFALSE) {
                simulated_blacklightOn = pdTRUE;
                printf("Key pressed, turning backlight ON at time\t%d\n",
                       tick_now);
            } else {
                printf("Key pressed, resetting software timer at time\t%d\n",
                       tick_now);
            }

            xTimerReset(blacklight_timer, pdMS_TO_TICKS(50));
        }
    }
}

int main(void)
{
    system_init();

    GPIO_SetMode(PE, BIT5, GPIO_MODE_INPUT);

    printf("Here is Lab Software Timer reset.\n");

    xTaskCreate(detect_task, "detect_task", 256, NULL, 1, NULL);

    blacklight_timer = xTimerCreate("BlackLightTimer", BLACKLIGHT_TIMER_PERIOD,
                                    pdFALSE, 0, blacklight_timer_callback);

    xTimerStart(blacklight_timer, 0);

    /* Start the scheduler. */
    vTaskStartScheduler();

    while (1) { ; }
}
