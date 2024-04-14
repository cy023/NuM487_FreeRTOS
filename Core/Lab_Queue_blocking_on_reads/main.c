#include <stdio.h>
#include "NuMicro.h"
#include "system.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

QueueHandle_t queue;

void sender_task(void *para)
{
    BaseType_t status;
    uint32_t send_data = (uint32_t) para;

    while (1) {
        status = xQueueSendToBack(queue, &send_data, 0);
        if (status != pdPASS) {
            printf("Could not send to the queue.\n");
        }
    }
}

void receiver_task(void *para)
{
    BaseType_t status;
    uint32_t recv_data;
    TickType_t timeout = pdMS_TO_TICKS(100);

    while (1) {
        if (uxQueueMessagesWaiting(queue) != 0) {
            printf("Queue should have been empty.\n");
        }

        status = xQueueReceive(queue, &recv_data, timeout);
        if (status == pdPASS) {
            printf("Received: %ld\n", recv_data);
        } else {
            printf("Could not receive from the queue.\n");
        }
    }
}

int main(void)
{
    system_init();

    printf("Here is Lab Queue Blocking on reads.\n");

    queue = xQueueCreate(5, sizeof(uint32_t));
    if (queue == NULL) {
        printf("Create queue fail.\n");
        return 0;
    }

    // Sender Task
    xTaskCreate(sender_task, "sender1", 256, (void *) 111, 1, NULL);
    xTaskCreate(sender_task, "sender2", 256, (void *) 222, 1, NULL);

    // Receiver Task
    xTaskCreate(receiver_task, "receiver", 256, NULL, 2, NULL);

    /* Start the scheduler. */
    vTaskStartScheduler();

    while (1) { ; }
}
