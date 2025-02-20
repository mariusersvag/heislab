#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#include "Elevator.h"
#include "OrderQueue.h"

typedef struct {
    bool go;
} Handler;

void run();

void initElevator();
void sortQueue(OrderQueue* p_queue, Elevator* p_elevator);
void processRequests();





