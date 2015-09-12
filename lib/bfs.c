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
#include "graph.h"
#include "queue.h"

bool processed[MAXV + 1]; /* which vertices have been processed */
bool discovered[MAXV + 1]; /* which vertices have been discovered */
int parent[MAXV + 1]; /* discovery relation */

void process_vertex_early(int v);
void process_vertex_late(int v);
void process_edge(int x, int y);


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
        process_vertex_early(v);
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
        /* process_vertex_late(v); */
    }
}

void process_vertex_early(int v)
{
    printf("processed edge %d\n", v);
}

/*
void process_vertex_late(int v)
{
}
*/

void process_edge(int x, int y)
{
    printf("processed edge (%d, %d)\n", x, y);
}
