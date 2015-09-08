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
        if (q->last) {
                q->last->next = l;
                q->last = l;
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
        Listptr head = q->first;
        if (head->next) {
                q->first = head->next;
        } else {
                q->first = NULL;
                q->last = NULL;
        }
        int item = head->item;
        free(head);
        return item;
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
        return l;
}
