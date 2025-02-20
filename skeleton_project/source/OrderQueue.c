#include "../include/OrderQueue.h"
#include "OrderQueue.h"

void clearQueue(OrderQueue* p_queue)
{
    for (int i = 0; i < QUEUESIZE+1; i++)
    {
        p_queue->queue[i].floor = -1;
    }
}

void addToQueue(OrderQueue* p_queue, QueueEntry entry)
{
    elevio_buttonLamp(entry.floor, entry.dir, 1);
    for (int i = 0; i < QUEUESIZE; i++)
    {
        if (p_queue->queue[i].floor != entry.floor)
        {
            if (p_queue->queue[i].floor == -1)
            {
                p_queue->queue[i] = entry;
                continue;
            }   
        
        } else if (entry.dir == BUTTON_CAB) break;

        else if (p_queue->queue[i].dir == BUTTON_CAB)
        {
            p_queue->queue[i].dir = entry.dir;
            continue;
        }
    }
}

void removeFromQueue(OrderQueue* p_queue, int floor)
{
    for (int i = 0; i < 3; i++) {
        elevio_buttonLamp(floor, i, 0);
    }
    int i = 0;
    while (p_queue->queue[i].floor == floor || p_queue->queue[i].floor == -1)
    {
        p_queue->queue[i] = p_queue->queue[i + 1];
        p_queue->queue[i + 1].floor = -1;
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
