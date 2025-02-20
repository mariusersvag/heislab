#pragma once

#include <stdbool.h>
#include "OrderQueue.h"
#include "driver/elevio.h"

typedef struct {
    int current_floor;
    bool door_open;
    MotorDirection motor_dir;
} Elevator;


void stop();
void arrived();
void moveTo(int floor);

void openDoor();
void closeDoor();

void updateCurrentFloor();
void setMotorDir(MotorDirection dir);

