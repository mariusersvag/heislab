#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "../include/Handler.h"

#define DOOR_OPEN_TIME_MS 1000
#define DOOR_OBS_TIME_MS 1000
#define LOOP_DELAY_MS 20

int main(){
    
    elevio_init();
    elevio_motorDirection(DIRN_STOP);

    Handler handler;
    handler.go = true;
    OrderQueue q = createQueue();
    Elevator elevator = createElevator();
    initElevator(&elevator);

    //Reset button lamps
    for (int etasje = 0; etasje < N_FLOORS; etasje++){
        for (ButtonType buttontype = 0; buttontype < N_BUTTONS; buttontype++) {
            elevio_buttonLamp(etasje, buttontype, 0);       
        }
    }
    elevio_stopLamp(0);
    
    int timer = 0;

    //Main loop
    while(handler.go){

        // printf("timer: %i\n", timer);

        if(elevio_stopButton())
        {
            emergencyStop(&elevator);
            break;
        }
        
        processRequests(&q, &elevator);
        printQueue(&q);

        //Dersom ikke tom kø
        if ((q.queue[0].floor != -1) && (timer <= 0))
        {
            moveTo(&elevator, q.queue[0].floor);
        } 
        else 
        {
            if (elevator.motor_dir != DIRN_STOP)
            {
                setMotorDir(&elevator, DIRN_STOP);  
            }
        }
        

        //Elevator arrived
        if (elevator.has_arrived)
        {   
            printf("ELEVATOR : arrived at floor %i\n", elevator.current_floor);
            removeFromQueue(&q, elevator.current_floor);
            openDoor(&elevator);
            timer += DOOR_OPEN_TIME_MS;
            elevator.has_arrived = false;
        } 
        
          
        //Door is ready to be closed
        if (timer <= 0 && elevator.door_open == true) 
        {
            if (elevio_obstruction()) 
            {
                timer += DOOR_OBS_TIME_MS;
                printf("ELEVATOR -> DOOR : obs!\n");
            }
            else
            {
                closeDoor(&elevator);
                timer = 0;
            } 
        }



        //Decrement timer
        if (timer > 0) timer -= LOOP_DELAY_MS;

        //20ms loop delay (for timer)
        nanosleep(&(struct timespec){0, LOOP_DELAY_MS*1000*1000}, NULL);        
    }
    return 0;
}
