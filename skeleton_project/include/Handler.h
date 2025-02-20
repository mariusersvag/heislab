#pragma once

#include <stdio.h>
#include <stdbool.h>

#include "Elevator.h"
#include "OrderQueue.h"

typedef struct {
    bool go;
} Handler;

void run();

void initElevator();
void sortQueue();
void processRequests();





