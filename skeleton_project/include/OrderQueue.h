#pragma once

#include <stdio.h>

#define QUEUESIZE 4

typedef struct {
    int queue[QUEUESIZE];
} OrderQueue;


// empties the whole queue
void clearQueue(OrderQueue* p_queue);

// adds a floor to the queue
void addToQueue(OrderQueue* p_queue, int floor); 

// removes a floor from the queue
void removeFromQueue(OrderQueue* p_queue, int floor);

void printQueue(OrderQueue* p_queue);

// Constructor for the OrderQueue struct
OrderQueue createQueue();