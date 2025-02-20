#include "../include/Handler.h"
#include "Handler.h"

void sortQueue(OrderQueue* p_queue, Elevator* p_elevator)
{
    
    
    for (int i = 0; i < QUEUESIZE; i++)
    {
        for (int j = 0; j < QUEUESIZE - i - 1; j++)
        {
            bool valid_index = p_queue->queue[j].floor != -1 && p_queue->queue[j + 1].floor != -1;
            if(!valid_index)
            {
                break;
            }
            bool queue_jp1_bgt_queue_j1 = p_queue->queue[j].floor < p_queue->queue[j + 1].floor;
            bool elevator_is_going_up = p_elevator->motor_dir == DIRN_UP;
            bool queue_jp1_bgt_prev_floor = p_queue->queue[j + 1].floor > p_elevator->previous_floor;
            bool queue_j_bge_prev_floor = p_queue->queue[j].floor >= p_elevator->previous_floor;
            bool queue_j_ble_prev_floor = p_queue->queue[j].floor <= p_elevator->previous_floor;
            bool jp1_right_direction = !(elevator_is_going_up ^ (p_queue->queue[j + 1].dir == BUTTON_HALL_UP)) || p_queue->queue[j + 1].dir == BUTTON_CAB; 

            //Elevator is going up
            bool swap = elevator_is_going_up && !queue_jp1_bgt_queue_j1 && queue_jp1_bgt_prev_floor;
            swap |= elevator_is_going_up && queue_jp1_bgt_queue_j1 && queue_j_ble_prev_floor;
            
            //Elevator is going down
            swap |= !elevator_is_going_up && queue_jp1_bgt_queue_j1 && !queue_jp1_bgt_prev_floor;
            swap |= !elevator_is_going_up && !queue_jp1_bgt_queue_j1 && queue_j_bge_prev_floor;

            swap |= jp1_right_direction;


            if (swap)
            {
                int temp = p_queue->queue[j].floor;
                p_queue->queue[j] = p_queue->queue[j + 1];
                p_queue->queue[j + 1].floor = temp;
            }
           
        }
    }
}

void processRequests(Elevator* p_elevator, OrderQueue* p_queue)
{
    for (int etasje = 0; etasje < N_FLOORS; etasje++){
        for (ButtonType buttontype = 0; buttontype < N_BUTTONS; buttontype++) {
            if (elevio_callButton(etasje, buttontype)){
                QueueEntry entry = {etasje, buttontype};
                addToQueue(p_queue, entry);
            }
        }
    }
} 

// int main()
// {
//     printf("Testing:\n\n");
//     Elevator heiss =  {0, 4, 0, -1};

//     OrderQueue navn = createQueue();

//     QueueEntry e1 = {1, BUTTON_HALL_UP};
//     QueueEntry e3 = {3, BUTTON_HALL_UP};
//     QueueEntry e2 = {2, BUTTON_HALL_UP};
//     QueueEntry e4 = {4, BUTTON_HALL_DOWN};
//     QueueEntry e5 = {3, BUTTON_HALL_DOWN};
//     QueueEntry e6 = {2, BUTTON_HALL_DOWN};
//     QueueEntry e7 = {1, BUTTON_CAB};
//     QueueEntry e8 = {2, BUTTON_CAB};
//     QueueEntry e9 = {3, BUTTON_CAB};
//     QueueEntry e10 = {4, BUTTON_CAB};    


//     addToQueue(&navn, e1);
//     addToQueue(&navn, e9);
//     addToQueue(&navn, e6);
//     addToQueue(&navn, e7);
//     printQueue(&navn);
//     sortQueue(&navn, &heiss);
//     printQueue(&navn);
//     return 0;
// }
