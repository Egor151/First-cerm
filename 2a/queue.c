#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "queue.h"

#ifdef VECTOR

int push(Queue *queue, double data) {
    if (queue == NULL) return 1;

    if (queue->size == MAX_SIZE) return 1;

    queue->data[queue->tail] = data;
    queue->tail = (queue->tail + 1) % MAX_SIZE ;
    queue->size += 1;

    return 0;
}

double get(Queue *queue) {
    if (queue == NULL) return NAN;

    if (queue->size == 0) return NAN;

    double res = queue->data[queue->head];
    queue->head = (queue->head + 1) % MAX_SIZE;
    queue->size -= 1;

    return res;
}

Queue *init_queue() {
    Queue *queue = malloc(sizeof(Queue));
    if (queue == NULL) return NULL;

    queue->size = 0;
    queue->data = malloc(MAX_SIZE * sizeof(double));

    if (queue->data == NULL) {
        free(queue);
        return NULL;
    }

    queue->head = 0;
    queue->tail = 0;

    return queue;
}

void free_queue(Queue *queue) {
    if (queue == NULL) {
        return;
    }

    free(queue->data);
    free(queue);
}

#else

int push(Queue *queue, double data) {
    Node *new = malloc(sizeof(Node));

    if (new == NULL) return 1;

    new->data = data;
    new->next = NULL;

    if (queue->head != NULL) {
        queue->tail->next = new;
    }
    else {
        queue->head = new;
    }

    queue->tail = new;

    return 0;
}

double get(Queue *queue) {
    if (queue == NULL) {
        return NAN;
    }

    if (queue->head == NULL) {
        return NAN;
    }

    Node *to_delete = queue->head;
    queue->head = to_delete->next;
    double ret = to_delete->data;

    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    free(to_delete);
    return ret;
}

Queue *init_queue() {
    Queue *queue = malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

void free_queue(Queue *queue) {
    Node *ptr = queue->head;

    while(ptr != NULL) {
        ptr = queue->head;
        queue->head = queue->head->next;
        free(ptr);
    }

    free(queue);
}

#endif
