#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

Queue *queue_new() {
    return (Queue *) calloc(1, sizeof(Queue));
}

void queue_delete(Queue *queue) {
    Item *ptr = queue->head, *ptr_prev;
    while (ptr) {
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev);
    }
    free(queue);
}

int queue_put(Queue *queue, int data) {
    Item *new = (Item *) malloc(sizeof(Item));
    if (!new) {
        return 1;
    }
    new->data = data;
    new->next = NULL;
    if (!queue->head) {
        queue->head = new;
        queue->tail = new;
    } else {
        queue->tail->next = new;
        queue->tail = new;
    }
    return 0;
}

int queue_get(Queue *queue, int *output) {
    if (!queue->head) {
        return 1;
    }
    *output = queue->head->data;
    if (queue->head == queue->tail) {
        queue->tail = NULL;
    }
    Item *head = queue->head;
    queue->head = head->next;
    free(head);
    return 0;
}

int queue_is_empty(Queue *queue){
    if (queue->head == NULL) {
        return 1;
    }
    return 0;
}

void queue_sort(Queue *queue) {
    Item *current = queue->head;
    Item *index = NULL;
    int temp;

    if (queue->head == NULL) {
        return;
    } else {
        while (current != NULL) {
            index = current->next;

            while (index != NULL) {
                if (current->data < index->data) {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }
                index = index->next;
            }
            current = current->next;
        }
    }
}

void queue_print(const Queue *queue) {
    Item *ptr = queue->head;
    while (ptr) {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}
