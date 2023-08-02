#include <stdlib.h>
#include "computation.h"
#include "mymath.h"

void place_task(Queue *compute, int angle, int nmemb) {
    push(compute, (double) angle);
    push(compute, (double) nmemb);
}

void compute(Queue *compute, Queue *result) {
    double angle, nmemb;
    angle = get(compute);
    nmemb = get(compute);

    double c_result = my_sin(angle, nmemb);

    push(result, angle);
    push(result, c_result);
}

void get_result(Queue *result, Result *table, int idx) {
    table[idx].angle = get(result);
    table[idx].result = get(result);
}
