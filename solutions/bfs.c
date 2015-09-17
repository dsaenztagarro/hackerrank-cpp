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

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#define MAXV 1000 /* Maximum number of nodes */

typedef struct edgenode * Edgenodeptr;

typedef struct edgenode {
    int y; /* adjacency info */
    int weight; /* edge weight, if any */
    Edgenodeptr next; /* next edge in list */
} edgenode;


typedef struct graph * Graphptr;

typedef struct graph {
    Edgenodeptr edges[MAXV+1];
    int degree[MAXV+1];
    int nvertices;
    int nedges;
    bool directed;
} graph;

typedef struct list * Listptr;

typedef struct list {
    int item; /* data item */
    Listptr next; /* point to successor */
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
Listptr listalloc(void);
Listptr create_itemlist(int i);

void initialize_graph(graph *g, bool directed);
void insert_edge(graph *graph, int x, int y, bool directed);
void read_graph(graph *g, bool directed);

void run_testcase();
void init_distances(int start_point);
void print_distances(graph * g, int start_point);
void print_distances_interval(int start, int end, int start_point, int *first);
void process_edge(int x, int y);
void bfs(graph *g, int start);


graph *gPtr;

int distances[MAXV + 1];
bool processed[MAXV + 1]; /* which vertices have been processed */
bool discovered[MAXV + 1]; /* which vertices have been discovered */
int parent[MAXV + 1]; /* discovery relation */

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


void initialize_search(graph *g)
{
        int i; /* counter */
        for (i = 0; i <= g->nvertices; i++) {
                processed[i] = discovered[i] = false;
                parent[i] = -1;
        }
}

void bfs(graph *g, int start)
{
        queue q; /* queue of vertices to visit */
        int v; /* current vertex */
        int y; /* successor vertex */
        edgenode *p; /* temporary pointer */

        init_queue(&q);
        enqueue(&q, start);
        discovered[start] = true;
        while(empty_queue(&q) == false) {
                v = dequeue(&q);
                processed[v] = true;
                p = g->edges[v];
                while (p != NULL) {
                        y = p->y;
                        if ((processed[y] == false) || g->directed)
                                process_edge(v, y);
                        if (discovered[y] == false) {
                                enqueue(&q, y);
                                discovered[y] = true;
                                parent[y] = v;
                        }
                        p = p->next;
                }
        }
}

void process_edge(int x, int y)
{
        if (distances[x] >= 0 && distances[y] < 0) {
                distances[y] = distances[x] + 6;
        } else if (distances[y] >= 0 && distances[x] < 0) {
                distances[x] = distances[y] + 6;
        }
}

void initialize_graph(graph *g, bool directed)
{
    int i; /* counter */

    g -> nvertices = 0;
    g -> nedges = 0;
    g -> directed = directed;

    for (i=1; i<=MAXV; i++) g->degree[i] = 0;
    for (i=1; i<=MAXV; i++) g->edges[i] = NULL;
}

void read_graph(graph *graph, bool directed)
{
    int i; /* counter */
    int nedges;
    int x, y; /* vertices in edge (x, y) */

    initialize_graph(graph, directed);

    scanf("%d %d",&(graph->nvertices), &nedges);

    for (i=1; i<=nedges; i++) {
        scanf("%d %d", &x, &y);
        insert_edge(graph, x, y, directed);
    }
}

void insert_edge(graph *graph, int x, int y, bool directed)
{
    edgenode *node;

    node = malloc(sizeof(edgenode));

    node->weight = 0;
    node->y = y;
    node->next = graph->edges[x];

    graph->edges[x] = node;
    graph->degree[x] ++;

    if (directed == false)
        insert_edge(graph, y, x, true);
    else
        graph->nedges ++;
}

int main()
{
        int i;
        int num_testcases;
        scanf("%d", &num_testcases);
        for (i = 0; i < num_testcases; i++) {
                run_testcase();
        }
        return 0;
}

void run_testcase()
{
        int start_point;
        graph g;
        graph *graphptr = &g;

        initialize_graph(graphptr, false);
        read_graph(graphptr, false);
        initialize_search(graphptr);

        scanf("%d", &start_point);
        init_distances(start_point);

        bfs(graphptr, start_point);
        print_distances(graphptr, start_point);
}

void init_distances(int start_point)
{
        int i;
        for (i = 0; i <= MAXV; i++) distances[i] = -1;
        distances[start_point] = 0;
}

void print_distances(graph * g, int start_point)
{
        int i;
        int first = 1;
        for (i = 1; i <= g->nvertices; i++) {
                if (i != start_point) {
                        if (first) {
                                printf("%d", distances[i]);
                                first = 0;
                        } else {
                                printf(" %d", distances[i]);
                        }
                }
        }
        printf("\n");
}
