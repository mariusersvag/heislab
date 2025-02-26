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

    Elevator elev = {c_f, p_f, 0, 0, DIRN_STOP};
    return elev;
}

void initElevator(Elevator* p_elevator)
{
    setMotorDir(p_elevator, DIRN_UP);
    //Go up until it hits a floor
    while( (elevio_floorSensor() != -1) && (!elevio_stopButton()) )
    {
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }
    setMotorDir(p_elevator, DIRN_STOP);

    p_elevator->current_floor = elevio_floorSensor();
    elevio_floorIndicator(p_elevator->current_floor);
    elevio_doorOpenLamp(p_elevator->door_open);

    //Edge cases (1 and 4)
    if (p_elevator->current_floor == 1) 
    {
        p_elevator->previous_floor = 2;
    }
    else if (p_elevator->current_floor == 4)
    {
        p_elevator->previous_floor = 3;
    }
    else 
    {
        p_elevator->previous_floor = (p_elevator->current_floor - 1);
    }
    return;
}

void moveTo(Elevator *p_elevator, int floor)
{

    //Arrived
    if (elevio_floorSensor() == floor) 
    {
        //Update floors
        p_elevator->previous_floor = p_elevator->current_floor;
        p_elevator->current_floor = floor;

        setMotorDir(p_elevator, DIRN_STOP);
        p_elevator -> has_arrived = true;
        sleep(3);
        return;
    }

    //UP and DOWN
    if ((p_elevator->current_floor) > floor)
    {
        setMotorDir(p_elevator, DIRN_DOWN);
    } 
    else 
    {
        setMotorDir(p_elevator, DIRN_UP);
    }
}



void openDoor(Elevator *p_elevator)
{
    if (p_elevator->motor_dir == DIRN_STOP) 
    {
        elevio_doorOpenLamp(1);
        p_elevator->door_open = true;
    }
}



void closeDoor(Elevator *p_elevator)
{   
    while (elevio_obstruction()) 
    {
        sleep(3);
    }

    elevio_doorOpenLamp(0);
    p_elevator->door_open = false;
}


//DELETE
void handleObstruction(Elevator *p_elevator)
{   
    printf("\nNot in use\n");
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





