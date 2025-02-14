#ifndef queue_h
#define queue_h

#include<stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "item.h"

typedef struct queue queue;

queue *create_queue(int size);

bool is_queue_empty(queue *q);

void insert_into_queue(queue *q, double dist, int id);

int remove_from_queue(queue *q); 

void change_distance_in_queue(queue *q, int id, double new_distance);

void free_queue(queue *q);

#endif