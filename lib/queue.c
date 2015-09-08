#include "queue.h"

Listptr listalloc(void);
Listptr create_itemlist(int i);

void init_queue(queue *q)
{
        q->first = NULL;
        q->last = NULL;
}

void enqueue(queue *q, int start)
{
        Listptr l = create_itemlist(start);
        if (q->first) {
                Listptr head = q->first;
                l->next = head;
                head->previous = l;
                q->first = l;
        } else {
                q->first = l;
                q->last = l;
        }
}

bool empty_queue(queue *q)
{
        return false;
}

int dequeue(queue *q)
{
        return 0;
}

Listptr listalloc(void)
{
        return (Listptr) malloc(sizeof(Listptr));
}

Listptr create_itemlist(int item)
{
        Listptr l = listalloc();
        l->item = item;
        l->next = NULL;
        l->previous = NULL;
        return l;
}
