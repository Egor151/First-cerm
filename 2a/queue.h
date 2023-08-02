#ifndef QUEUE_H
#define QUEUE_H

#define MAX_SIZE 128

#ifdef VECTOR

typedef struct Queue {
    double *data;
    int size;
    int head;
    int tail;
} Queue;

#else

typedef struct Node {
    double data;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *head;
    Node *tail;
} Queue;

#endif

int push(Queue *queue, double data);

double get(Queue *queue);

Queue *init_queue();

void free_queue(Queue *queue);

#endif
