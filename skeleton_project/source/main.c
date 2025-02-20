#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "../include/Handler.h"

// FIKS KONSTRUKTOREN TIL ELEVATOR
int main(){
    
    elevio_init();
    
    elevio_motorDirection(DIRN_STOP);

    Handler handler;
    handler.go = true;

    OrderQueue q = createQueue();
    Elevator elevator = createElevator();




    for (int etasje = 0; etasje < N_FLOORS; etasje++){
        for (ButtonType buttontype = 0; buttontype < N_BUTTONS; buttontype++) {
            elevio_buttonLamp(etasje, buttontype, 0);
            
        }
    }
    elevio_stopLamp(0);
    

    while(handler.go){

        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }

        processRequests(&q, &elevator);
        sortQueue(&q, &elevator);
        if (q.queue[0].floor != -1) {
            moveTo(&elevator, q.queue[0].floor);
        } else {
            elevio_motorDirection(DIRN_STOP);
        }


        





        




        // elevio_floorIndicator(2);
        // sleep(3);    
    
        // elevio_floorIndicator(3);
        // sleep(3);    
        
        // elevio_floorIndicator(1);
        // sleep(3);  


        // int floor = elevio_floorSensor();

        // if(floor == 0){
        //     elevio_motorDirection(DIRN_UP);
        // }

        // if(floor == N_FLOORS-1){
        //     elevio_motorDirection(DIRN_DOWN);
        // }


        // for(int f = 0; f < N_FLOORS; f++){
        //     for(int b = 0; b < N_BUTTONS; b++){
        //         int btnPressed = elevio_callButton(f, b);
        //         elevio_buttonLamp(f, b, btnPressed);
        //     }
        // }

        // if(elevio_obstruction()){
        //     elevio_stopLamp(1);
        // } else {
        //     elevio_stopLamp(0);
        // }
        
        // if(elevio_stopButton()){
        //     elevio_motorDirection(DIRN_STOP);
        //     break;
        // }
        
        // nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
