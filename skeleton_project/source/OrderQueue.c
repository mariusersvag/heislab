#include "../include/OrderQueue.h"

void clearQueue(OrderQueue* p_queue)
{
    for (int i = 0; i < QUEUESIZE; i++)
    {
        p_queue->queue[i].floor = -1;
        
    }
}

void addToQueue(OrderQueue* p_queue, QueueEntry entry)
{
    elevio_buttonLamp(entry.floor, entry.dir, 1);

    for (int i = 0; i < QUEUESIZE; i++)
    {
        int queue_floor = p_queue->queue[i].floor;


        //Dersom floor allerede er i køen, forkast forespørsel men endre dir?
        if (queue_floor == entry.floor) 
        {
            p_queue->queue[i].dir = entry.dir;
            return;
        };

        //Setter inn i frammerste -1 verdi
        if (queue_floor == -1)
        {
            p_queue->queue[i] = entry;
            return;  
        } 


        // //Fra den gamle koden
        // if (p_queue->queue[i].dir == BUTTON_CAB) 
        // {
        //     p_queue->queue[i].dir = entry.dir;
        // }

        // //LOL


        // if (p_queue->queue[i].dir == BUTTON_CAB)
        // {
        //     p_queue->queue[i].dir = entry.dir;
        //     continue;
        // }

    }
}

void removeFromQueue(OrderQueue* p_queue, int floor)
{
    for (int i = 0; i < 3; i++) {
        elevio_buttonLamp(floor, i, 0);
    }

    // Iterate over the queue and shift elements left when the floor is found
    for (int i = 0; i < QUEUESIZE - 1; i++) {
        if (p_queue->queue[i].floor == floor) {
            // Shift the remaining elements to the left
            for (int j = i; j < QUEUESIZE - 1; j++) {
                p_queue->queue[j] = p_queue->queue[j + 1];
            }
            // Mark the last position as empty
            p_queue->queue[QUEUESIZE - 1].floor = -1;
            break; // Stop once the first match is removed
        }
    }
    
    // int i = 0;
    // while (p_queue->queue[i].floor == floor || p_queue->queue[i].floor == -1)
    // {
    //     p_queue->queue[i] = p_queue->queue[i + 1];
    //     p_queue->queue[i + 1].floor = -1;
    //     i++;
    // }
}

void printQueue(OrderQueue *p_queue)
{
    static OrderQueue last_queue; // Store the last printed queue

    int isQueueDifferent = 0;
    for (int i = 0; i < QUEUESIZE; i++) {
        if (p_queue->queue[i].floor != last_queue.queue[i].floor) {
            isQueueDifferent = 1;
            break;
        }
    }

    if (isQueueDifferent) {
        printf("QUEUE : [");
        for (int i = 0; i < QUEUESIZE; i++) 
        {
            printf("%i, ", p_queue->queue[i].floor);    
        }
        printf("]\n");

        for (int i = 0; i < QUEUESIZE; i++) {
            last_queue.queue[i] = p_queue->queue[i];
        }
    }

    // static OrderQueue last_queue;
    // printf("Queue: [");
    // for (int i = 0; i < QUEUESIZE; i++)
    // {
    //     printf("%i, ", p_queue->queue[i]);
    // }
    // printf("]\n");
}

OrderQueue createQueue()
{
    OrderQueue queue;
    clearQueue(&queue);
    return queue;
}
