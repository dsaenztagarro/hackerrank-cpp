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
#include "main.h"
#include "graph.h"

int distancess[MAXV+1]; /* distances vertex is from start */

void dijkstra(graph *g, int start)
{
        int i; /* counter */
        edgenode *p; /* temporary pointer */
        bool intree[MAXV+1]; /* is the vertex in the tree yet? */
        int parent[MAXV + 1]; /* discovery relation */
        int v; /* current vertex to process */
        int w; /* candidate next vertex */
        int cweight; /* weight from start to current vertex */
        int dist; /* best current distances from start */

        for (i=1; i<=g->nvertices; i++) {
                intree[i] = false;
                distances[i] = MAXINT;
                parent[i] = -1;
        }
        distances[start] = 0;
        v = start;
        while (intree[v] == false) {
                intree[v] = true;
                p = g->edges[v];
                while (p != NULL) {
                        w = p->y;
                        cweight = distances[v] + p->weight;
                        if (distances[w] > cweight) {
                                distances[w] = cweight;
                                parent[w] = v;
                        }
                        p = p->next;
                }
                v = 1;
                dist = MAXINT;
                for (i=1; i<=g->nvertices; i++)
                        if ((intree[i] == false) && (dist > distances[i])) {
                                dist = distances[i];
                                v = i;
                        }
        }
}
