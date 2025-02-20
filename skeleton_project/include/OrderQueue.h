#pragma once
#define QUEUESIZE 4

typedef struct {
    int queue[4];
} OrderQueue;


// empties the whole queue
void clear_queue(int* p_queue[QUEUESIZE]);

// adds a floor to the queue
void add_to_queue(int floor); 

