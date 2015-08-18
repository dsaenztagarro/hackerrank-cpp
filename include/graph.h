#ifndef GRAPH_H
#define GRAPH_H

#include<stdbool.h>

#define MAXV 1000 /* Maximum number of nodes */

typedef struct {
  int y; /* adjacency info */
  int weight; /* edje weight, if any */
  struct edgenode *next;
} edgenode;

typedef struct {
  edgenode *edges[MAXV+1];
  int degree[MAXV+1];
  int nvertices;
  int nedges;
  bool directed;
} graph;

void initialize_graph(graph *g, bool directed);


#endif
