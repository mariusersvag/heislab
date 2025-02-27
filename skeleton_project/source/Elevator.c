#include <time.h>
#include "../include/Elevator.h"

void stop(Elevator *p_elevator)
{
    setMotorDir(p_elevator, DIRN_STOP);
    elevio_stopLamp(1);
}



Elevator createElevator()
{   
    Elevator elev = {1, 1, 0, 0, DIRN_STOP};
    return elev;
}

void initElevator(Elevator* p_elevator)
{
    // setMotorDir(p_elevator, DIRN_UP);
    // //Go up until it hits a floor
    // while( (elevio_floorSensor() != -1) && (!elevio_stopButton()) )
    // {
    //     nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    // }
    // setMotorDir(p_elevator, DIRN_STOP);

    p_elevator->current_floor = elevio_floorSensor();
    elevio_floorIndicator(p_elevator->current_floor);
    elevio_doorOpenLamp(p_elevator->door_open);

    //Edge cases (1 and 4)
    if (p_elevator->current_floor == 0) 
    {
        p_elevator->previous_floor = 1;
    }
    else if (p_elevator->current_floor == 3)
    {
        p_elevator->previous_floor = 2;
    }
    else 
    {
        p_elevator->previous_floor = (p_elevator->current_floor - 1);
    }
    printf("ELEVATOR -> INIT : cf, pf = {%i, %i}\n", p_elevator->current_floor, p_elevator->previous_floor);
    return;
}

void moveTo(Elevator *p_elevator, int floor)
{   
    //Floor lights
    int floor_sensor = elevio_floorSensor();
    if (floor_sensor != -1) 
    {
        elevio_floorIndicator(floor_sensor);
    }

    //Arrived
    if (floor_sensor == floor) 
    {
        //Update floors
        p_elevator->previous_floor = p_elevator->current_floor;
        p_elevator->current_floor = floor;
        setMotorDir(p_elevator, DIRN_STOP);
        p_elevator->has_arrived = true;
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
    printf("ELEVATOR -> DOOR : door is OPEN\n");
}



void closeDoor(Elevator *p_elevator)
{   
    while (elevio_obstruction()) 
    {
        sleep(3);
        printf("ELEVATOR -> DOOR : obs!\n");
    }

    elevio_doorOpenLamp(0);
    p_elevator->door_open = false;

    printf("ELEVATOR -> DOOR : door is CLOSED\n\n");

}


//DELETE
void handleObstruction(Elevator *p_elevator)
{   
    int ikke_i_bruk = 2;
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





