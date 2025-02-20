#include "../include/Handler.h"

void sortQueue(OrderQueue* p_queue, Elevator* p_elevator)
{
    for (int i = 0; i < QUEUESIZE; i++)
    {
        for (int j = 0; j < QUEUESIZE - i - 1; j++)
        {
            bool valid_index = p_queue->queue[j] != -1 && p_queue->queue[j + 1] != -1;
            if(!valid_index)
            {
                break;
            }
            bool queue_jp1_bgt_queue_j1 = p_queue->queue[j] < p_queue->queue[j + 1];
            bool elevator_is_going_up = p_elevator->motor_dir == DIRN_UP;
            bool queue_jp1_bgt_prev_floor = p_queue->queue[j + 1] > p_elevator->previous_floor;
            bool queue_j_bge_prev_floor = p_queue->queue[j] >= p_elevator->previous_floor;
            bool queue_j_ble_prev_floor = p_queue->queue[j] <= p_elevator->previous_floor;


            bool swap = elevator_is_going_up && !queue_jp1_bgt_queue_j1 && queue_jp1_bgt_prev_floor;
            swap |= !elevator_is_going_up && queue_jp1_bgt_prev_floor && !queue_jp1_bgt_prev_floor;
            swap |= elevator_is_going_up && queue_jp1_bgt_queue_j1 && queue_j_ble_prev_floor;
            swap |= !elevator_is_going_up && !queue_jp1_bgt_queue_j1 && queue_j_bge_prev_floor;


            if (swap)
            {
                int temp = p_queue->queue[j];
                p_queue->queue[j] = p_queue->queue[j + 1];
                p_queue->queue[j + 1] = temp;
            }
           
        }
    }
}