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
  int nedges;
  int x, y; /* vertices in edge (x, y) */

  initialize_graph(graph, directed);

  scanf("%d %d",&(graph->nvertices), &nedges);

  for (int i=1; i<nedges; i++) {
    scanf("%d %d", &x, &y);
    insert_edge(graph, x, y, directed);
  }
}

void insert_edge(graph *graph, int x, int y, bool directed)
{
  edgenode *node;

  node = malloc(sizeof(edgenode));

  node->weight = NULL;
  node->y = y;
  node->next = graph->edges[x];

  graph->edges[x] = node;
  graph->degree[x] ++;

  if (directed == FALSE)
    insert_edge(graph, y, x, TRUE);
  else
    graph->nedges ++;
}

void print_graph(graph* graph)
{
  edgenode *node;

  for (int i=1; i<=graph->nvertices; i++)
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
