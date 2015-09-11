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

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

void insert_edge(graph *graph, int x, int y, bool directed);

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

void print_graph(graph* graph)
{
    int i; /* counter */
    edgenode *node;

    for (i=1; i<=graph->nvertices; i++)
    {
        printf("%d: ", i);
        node = graph->edges[i];
        while (node != NULL) {
            printf(" %d", node->y);
            node = node->next;
        }
        printf("\n");
    }
}
