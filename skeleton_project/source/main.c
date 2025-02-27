#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "../include/Handler.h"

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
    

    //Main loop
    while(handler.go){

        if(elevio_stopButton())
        {
            emergencyStop(&elevator);
            break;
        }
        
        processRequests(&q, &elevator);
        printQueue(&q);

        //Dersom ikke tom kø
        if (q.queue[0].floor != -1) 
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
        
        if (elevator.has_arrived)
        {   
            printf("ELEVATOR : arrived at floor %i\n", elevator.current_floor);
            removeFromQueue(&q, elevator.current_floor);
            // sortQueue(&q, &elevator);
            // sleep(3);
            openDoor(&elevator);
            sleep(1);
            closeDoor(&elevator);
            // sleep(3);
            elevator.has_arrived = false;
        } 
    }
    return 0;
}

//20ms loop delay
// nanosleep(&(struct timespec){0, 10*1000*1000}, NULL);        