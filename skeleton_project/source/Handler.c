#include "../include/Handler.h"



void arrived(OrderQueue* p_queue, Elevator *p_elevator) 
{
    //Zero indexed lights
    elevio_floorIndicator(p_elevator->current_floor - 1);
    removeFromQueue(p_queue, p_elevator->current_floor);
    sleep(3);
}




void sortQueue(OrderQueue* p_queue, Elevator* p_elevator)
{
    for (int i = 0; i < QUEUESIZE; i++)
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
                bool elevator_is_going_down = p_elevator->motor_dir == DIRN_DOWN;
                bool queue_jp1_bgt_prev_floor = p_queue->queue[j + 1].floor > p_elevator->previous_floor + 1;
                bool queue_j_bge_prev_floor = p_queue->queue[j].floor >= p_elevator->previous_floor;
                bool queue_j_ble_prev_floor = p_queue->queue[j].floor <= p_elevator->previous_floor;

                bool jp1_right_direction = elevator_is_going_up && (p_queue->queue[j + 1].dir == BUTTON_HALL_UP);
                jp1_right_direction |= !elevator_is_going_up && (p_queue->queue[j + 1].dir == BUTTON_HALL_DOWN);
                jp1_right_direction |= p_queue->queue[j + 1].dir == BUTTON_CAB; 

                //Elevator is going up
                bool swap = elevator_is_going_up && !queue_jp1_bgt_queue_j1 && queue_jp1_bgt_prev_floor;
                swap |= elevator_is_going_up && queue_jp1_bgt_queue_j1 && queue_j_ble_prev_floor;
                
                //Elevator is going down
                swap |= elevator_is_going_down && queue_jp1_bgt_queue_j1 && !queue_jp1_bgt_prev_floor;
                swap |= elevator_is_going_down && !queue_jp1_bgt_queue_j1 && queue_j_bge_prev_floor;

                swap &= jp1_right_direction;

                //heihei
                if (swap)
                {
                    int temp = p_queue->queue[j].floor;
                    p_queue->queue[j] = p_queue->queue[j + 1];
                    p_queue->queue[j + 1].floor = temp;
                }
            
            }
        }
    }
}


void sortQueue2(OrderQueue* queue, Elevator* elev) 
{
    bool elev_up = elev->motor_dir == DIRN_UP;

    for (int i = 0; i < QUEUESIZE; i++) 
    {
        for (int j = 0; j < QUEUESIZE - i - 1; j++) 
        {
            bool valid_index = queue->queue[j].floor != -1 && queue->queue[j + 1].floor != -1;
            if (!valid_index) 
            {
                break;
            }

            bool swap = false;

            if (elev_up) 
            {
                // Prioritize CAB first, then hall up, then hall down
                if (queue->queue[j].dir == BUTTON_CAB && queue->queue[j + 1].dir != BUTTON_CAB) 
                {
                    swap = false;
                } 
                else if (queue->queue[j].dir != BUTTON_CAB && queue->queue[j + 1].dir == BUTTON_CAB) 
                {
                    swap = true;
                } 
                else if (queue->queue[j].dir == BUTTON_HALL_UP && queue->queue[j + 1].dir == BUTTON_HALL_DOWN) 
                {
                    swap = false;
                } 
                else if (queue->queue[j].dir == BUTTON_HALL_DOWN && queue->queue[j + 1].dir == BUTTON_HALL_UP) 
                {
                    swap = true;
                } 
                else 
                {
                    swap = queue->queue[j].floor > queue->queue[j + 1].floor;
                }
            } 
            else 
            {
                // Prioritize CAB first, then hall down, then hall up
                if (queue->queue[j].dir == BUTTON_CAB && queue->queue[j + 1].dir != BUTTON_CAB) 
                {
                    swap = false;
                } 
                else if (queue->queue[j].dir != BUTTON_CAB && queue->queue[j + 1].dir == BUTTON_CAB) 
                {
                    swap = true;
                } 
                else if (queue->queue[j].dir == BUTTON_HALL_DOWN && queue->queue[j + 1].dir == BUTTON_HALL_UP) 
                {
                    swap = false;
                } 
                else if (queue->queue[j].dir == BUTTON_HALL_UP && queue->queue[j + 1].dir == BUTTON_HALL_DOWN) 
                {
                    swap = true;
                } 
                else 
                {
                    swap = queue->queue[j].floor < queue->queue[j + 1].floor;
                }
            }

            if (swap) 
            {
                QueueEntry temp = queue->queue[j];
                queue->queue[j] = queue->queue[j + 1];
                queue->queue[j + 1] = temp;
            }
        }
    }
}

void processRequests(OrderQueue* p_queue, Elevator* p_elevator)
{
    // sortQueue(p_queue, p_elevator);
    for (int etasje = 0; etasje < N_FLOORS; etasje++){
        for (ButtonType buttontype = 0; buttontype < N_BUTTONS; buttontype++) {
            
            if (elevio_callButton(etasje, buttontype))
            {
                int exist = 0;
                for (int i = 0; i < QUEUESIZE; i++) if (p_queue->queue[i].floor == etasje)
                {exist = 1;
                // sortQueue(p_queue, p_elevator);
                }  
                if (!exist) 
                {
                    QueueEntry entry = {etasje, buttontype};
                    addToQueue(p_queue, entry);
                    sortQueue(p_queue, p_elevator);
                }
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
