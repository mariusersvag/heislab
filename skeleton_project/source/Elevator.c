#include <time.h>
#include "../include/Elevator.h"
#include "Elevator.h"

void stop(Elevator *p_elevator)
{
    setMotorDir(p_elevator, DIRN_STOP);
    elevio_stopLamp(1);
}

Elevator createElevator()
{   
    Elevator elev;
    return elev;
}


void arrived(Elevator *p_elevator) 
{
    //Zero indexed lights
    elevio_floorIndicator(p_elevator->current_floor - 1);
}



void moveTo(Elevator *p_elevator, int floor)
{
    if ((p_elevator->current_floor == 4) || (p_elevator->current_floor > floor)){
        setMotorDir(p_elevator, DIRN_DOWN);
    }
    else {
        setMotorDir(p_elevator, DIRN_UP);

    
    
    }
}



void openDoor(Elevator *p_elevator)
{
    elevio_doorOpenLamp(1);
    p_elevator->door_open = 1;
}



void closeDoor(Elevator *p_elevator)
{   
    bool obs = elevio_obstruction();
    if (obs) handleObstruction(p_elevator);

    elevio_doorOpenLamp(0);
    p_elevator->door_open = 0;
}



void updateCurrentFloor(Elevator *p_elevator)
{
    p_elevator->current_floor = elevio_floorSensor();
}



void setMotorDir(Elevator *p_elevator, MotorDirection dir)
{
    elevio_motorDirection(dir);
    p_elevator->motor_dir = dir;
}



void emergencyStop(Elevator *p_elevator)
{
    elevio_motorDirection(DIRN_STOP);
    p_elevator->motor_dir = DIRN_STOP;
}



void handleObstruction(Elevator *p_elevator)
{
    //Sleep for 3s
    sleep(3);
    closeDoor(p_elevator);
}


