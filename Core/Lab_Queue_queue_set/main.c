#include <stdio.h>
#include "NuMicro.h"
#include "system.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

QueueHandle_t queue1, queue2;
QueueSetHandle_t queue_set;

void sender1_task(void *para)
{
    BaseType_t status;
    char *str = (char *) para;

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(100));

        status = xQueueSendToBack(queue1, &str, 0);
        if (status != pdPASS) {
            printf("Could not send to the queue.\n");
        }
    }
}

void sender2_task(void *para)
{
    BaseType_t status;
    char *str = (char *) para;

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(200));

        status = xQueueSendToBack(queue2, &str, 0);
        if (status != pdPASS) {
            printf("Could not send to the queue.\n");
        }
    }
}

void receiver_task(void *para)
{
    QueueHandle_t q_available;
    BaseType_t status;
    char *recv_data;

    while (1) {
        q_available =
            (QueueHandle_t) xQueueSelectFromSet(queue_set, portMAX_DELAY);

        status = xQueueReceive(q_available, &recv_data, 0);
        if (status == pdPASS) {
            printf("%s\n", recv_data);
        } else {
            printf("Could not receive from the queue.\n");
        }
    }
}

int main(void)
{
    system_init();

    printf("Here is Lab Queue queue set.\n");

    queue1 = xQueueCreate(1, sizeof(char *));
    queue2 = xQueueCreate(1, sizeof(char *));

    queue_set = xQueueCreateSet(2);

    xQueueAddToSet(queue1, queue_set);
    xQueueAddToSet(queue2, queue_set);

    // Sender Task
    xTaskCreate(sender1_task, "sender1", 256, "Sender1 Task Message.", 1, NULL);
    xTaskCreate(sender2_task, "sender2", 256, "Sender2 Task Message.", 1, NULL);

    // Receiver Task
    xTaskCreate(receiver_task, "receiver", 256, NULL, 2, NULL);

    /* Start the scheduler. */
    vTaskStartScheduler();

    while (1) { ; }
}
