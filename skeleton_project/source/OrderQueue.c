#include "../include/OrderQueue.h"
#include "OrderQueue.h"

void clearQueue(OrderQueue* p_queue)
{
    for (int i = 0; i < QUEUESIZE+1; i++)
    {
        p_queue->queue[i] = -1;
    }
}

void addToQueue(OrderQueue* p_queue, int floor)
{
    for (int i = 0; i < QUEUESIZE; i++)
    {
        if (p_queue->queue[i] == -1)
        {
            p_queue->queue[i] = floor;
            break;
        }
    }

}

void removeFromQueue(OrderQueue* p_queue, int floor)
{
    int i = 0;
    while (p_queue->queue[i] == floor || p_queue->queue[i] == -1)
    {
        p_queue->queue[i] = p_queue->queue[i + 1];
        p_queue->queue[i + 1] = -1;
        i++;
    }
}

void printQueue(OrderQueue *p_queue)
{
    printf("Queue: [");
    for (int i = 0; i < QUEUESIZE; i++){
        printf("%i, ", p_queue->queue[i]);
    }
    printf("]\n");
}



OrderQueue createQueue()
{
    OrderQueue queue;
    clearQueue(&queue);
    return queue;
}
