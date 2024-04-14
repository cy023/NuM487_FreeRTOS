#include <stdio.h>
#include "NuMicro.h"
#include "system.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

typedef enum {
    sender1,
    sender2
} datasrc_t;

typedef struct {
    datasrc_t datasrc;
    uint32_t val;
} data_t;

QueueHandle_t queue;

data_t tx_data[2] = {
    {sender1, 111},
    {sender2, 222},
};

void sender_task(void *para)
{
    BaseType_t status;
    TickType_t timeout = pdMS_TO_TICKS(100);

    while (1) {
        status = xQueueSendToBack(queue, para, timeout);
        if (status != pdPASS) {
            printf("Could not send to the queue.\n");
        }
    }
}

void receiver_task(void *para)
{
    BaseType_t status;
    data_t recv_data;

    while (1) {
        if (uxQueueMessagesWaiting(queue) != 3) {
            printf("Queue should have been full.\n");
        }

        status = xQueueReceive(queue, &recv_data, 0);
        if (status == pdPASS) {
            if (recv_data.datasrc == sender1) {
                printf("Receive from sender1: %ld\n", recv_data.val);
            } else if (recv_data.datasrc == sender2) {
                printf("Receive from sender2: %ld\n", recv_data.val);
            }
        } else {
            printf("Could not receive from the queue.\n");
        }
    }
}

int main(void)
{
    system_init();

    printf("Here is Lab Queue Blocking on writes.\n");

    queue = xQueueCreate(3, sizeof(data_t));
    if (queue == NULL) {
        printf("Create queue fail.\n");
        return 0;
    }

    // Sender Task
    xTaskCreate(sender_task, "sender1", 256, &(tx_data[0]), 2, NULL);
    xTaskCreate(sender_task, "sender2", 256, &(tx_data[1]), 2, NULL);

    // Receiver Task
    xTaskCreate(receiver_task, "receiver", 256, NULL, 1, NULL);

    /* Start the scheduler. */
    vTaskStartScheduler();

    while (1) { ; }
}
