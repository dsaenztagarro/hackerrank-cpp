/**
 * Copyright (C) 2015, David Saenz Tagarro
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
        return q->first == NULL;
}

int dequeue(queue *q)
{
        int item; /* item dequeued */
        Listptr head = q->first;
        if (head->next) {
                q->first = head->next;
        } else {
                q->first = NULL;
                q->last = NULL;
        }
        item = head->item;
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
