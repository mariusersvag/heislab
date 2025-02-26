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
        sortQueue(&q, &elevator);

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
            printf("\nELEVATOR : arrived at floor %i\n", elevator.current_floor);
            elevio_floorIndicator(elevator.current_floor - 1);
            removeFromQueue(&q, elevator.current_floor);
            sleep(3);

            openDoor(&elevator);
            printf("\nELEVATOR : door is open\n");
            sleep(3);

            closeDoor(&elevator);
            printf("\nELEVATOR : door is closed\n");
            sleep(3);

            elevator.has_arrived = false;
        }
        
        //20ms loop delay
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);        
    }

    return 0;
}
