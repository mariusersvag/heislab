#include <time.h>
#include "../include/Elevator.h"

void stop(Elevator *p_elevator)
{
    setMotorDir(p_elevator, DIRN_STOP);
    elevio_stopLamp(1);
}



Elevator createElevator()
{   
    int c_f = elevio_floorSensor();    
    int p_f;

    if (c_f == 1) p_f = 2;
    else if (c_f == 2) p_f = 1;
    else if (c_f == 3) p_f = 2;
    else if (c_f == 4) p_f = 3;

    Elevator elev = {c_f, p_f, 0, DIRN_STOP};
    return elev;
}




void moveTo(Elevator *p_elevator, int floor)
{
    updateCurrentFloor(p_elevator);

    //Arrived
    if (p_elevator->current_floor == floor) {
        setMotorDir(p_elevator, DIRN_STOP);
        // arrived(p_elevator);
    }

    //Queue is empty
    if (floor == -1) {
        setMotorDir(p_elevator, DIRN_STOP);
    }

    //Normal mode
    if ((p_elevator->current_floor > floor)){
        setMotorDir(p_elevator, DIRN_DOWN);
    } else {
        setMotorDir(p_elevator, DIRN_UP);
    }
}



void openDoor(Elevator *p_elevator)
{

    if (p_elevator->motor_dir == DIRN_STOP) {
        elevio_doorOpenLamp(1);
        p_elevator->door_open = 1;
    }
}



void closeDoor(Elevator *p_elevator)
{   
    bool obs = elevio_obstruction();
    if (obs) {
        handleObstruction(p_elevator);
    } else {
        elevio_doorOpenLamp(0);
        p_elevator->door_open = 0;
    }
}


void handleObstruction(Elevator *p_elevator)
{
    //Sleep for 3s
    sleep(3);
    closeDoor(p_elevator);
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





