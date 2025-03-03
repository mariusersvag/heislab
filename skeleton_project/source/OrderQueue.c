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
        int q_floor = p_queue->queue[i].floor;
        int q_dir = p_queue->queue[i].dir;

        //Dersom floor er i Queue
        if ((q_floor == entry.floor)) 
        {
            // if (q_dir == BUTTON_CAB) 
            // {
            //     p_queue->queue[i].dir = entry.dir;
            //     return;
            // }

            //Dersom entry er i Queue
            if (entry.dir == BUTTON_CAB) {
                p_queue->queue[i].dir = BUTTON_CAB;
                return;
            }
            else if (q_dir == BUTTON_CAB) return;
            else if (q_dir == entry.dir) return;
            else {
                p_queue->queue[i].dir = BUTTON_CAB; //BUTTON_CAB means dont care in this context
                return;
            }
        }

        //Setter inn i frammerste -1 verdi
        if (q_floor == -1)
        {
            p_queue->queue[i] = entry; 
            return;  
        } 
    }


    /*
    for (int i = 0; i < QUEUESIZE; i++)
    {
        if (p_queue->queue[i].floor != entry.floor)
        {
            if (p_queue->queue[i].floor == -1)
            {
                p_queue->queue[i] = entry;
                return;
            }   
        
        } 
        
        else if (p_queue->queue[i].dir == BUTTON_CAB)
        {
            p_queue->queue[i].dir = entry.dir;
            return;
        }

        else if (entry.dir == BUTTON_CAB) return;

        return;
    }   
    */
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
    static OrderQueue last_queue; // Forrige kø

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
}

OrderQueue createQueue()
{
    OrderQueue queue;
    clearQueue(&queue);
    return queue;
}
