#include "Elevator.h"

void closeDoor(Elevator *p_elevator)
{   
    p_elevator->door_open = 0;
}

void updateCurrentFloor(Elevator *p_elevator)
{
    p_elevator->current_floor = elevio_floorSensor();
}

void setMotorDir(Elevator *p_elevator, MotorDirection dir)
{
    p_elevator->motor_dir = dir;
}
