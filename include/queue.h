#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct queue {
        int item; /* data item */
        struct queue *next; /* point to successor */
} queue;

void init_queue(queue *q);
void enqueue(queue *q, int start);
bool empty_queue(queue *q);
queue dequeue(queue *q);

#endif
