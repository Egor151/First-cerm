#ifndef COMPUTATION_H
#define COMPUTATION_H

#include "queue.h"

typedef struct Result {
    int angle;
    double result;
} Result;

void place_task(Queue *compute, int angle, int nmemb);

void compute(Queue *compute, Queue *result);

void get_result(Queue *result, Result *table, int idx);

#endif // COMPUTATION_H
