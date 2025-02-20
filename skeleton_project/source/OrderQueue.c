#include "OrderQueue.h"

void clear_queue(int *p_queue)
{
    for (int i = 0; i < QUEUESIZE; i++)
    {
        p_queue[i] = -1;
    }
}

void add_to_queue(int *p_queue, int floor)
{
    for (int i = 0; i < QUEUESIZE; i++)
    {
        if (p_queue[i] == -1)
        {
            p_queue[i] = floor;
            break;
        }
    }

}
