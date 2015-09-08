#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct list * Listptr;

typedef struct list {
    int item; /* data item */
    Listptr next; /* point to successor */
    Listptr previous; /* point to precessor */
} list;

typedef struct queue * Queueptr;

typedef struct queue {
        Listptr first; /* point to successor */
        Listptr last; /* point to last item */
} queue;

void init_queue(queue *q);
void enqueue(queue *q, int start);
bool empty_queue(queue *q);
int dequeue(queue *q);

#endif
