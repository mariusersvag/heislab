#include "Elevator.h"

void openDoor(Elevator *p_elevator)
{
    elevio_doorOpenLamp(1);
    p_elevator->door_open = 1;
}

void closeDoor(Elevator *p_elevator)
{   
    elevio_doorOpenLamp(0);
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

void emergencyStop(Elevator *p_elevator)
{
    elevio_motorDirection(DIRN_STOP);
    p_elevator->motor_dir = DIRN_STOP;
}
