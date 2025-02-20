#pragma once

#include <stdbool.h>
#include "OrderQueue.h"
#include "../source/driver/elevio.h"

typedef struct {
    int current_floor;
    int previous_floor;
    bool door_open;
    MotorDirection motor_dir;
} Elevator;


void stop(Elevator* p_elevator);
void arrived(Elevator* p_elevator);
void moveTo(Elevator* p_elevator, int floor);

void openDoor(Elevator* p_elevator);
void closeDoor(Elevator* p_elevator);

void updateCurrentFloor(Elevator* p_elevator);
void setMotorDir(Elevator* p_elevator, MotorDirection dir);

void emergencyStop(Elevator* p_elevator);
void handleObstruction(Elevator* p_elevator);

