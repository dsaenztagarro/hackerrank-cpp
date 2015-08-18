#include <stdbool.h>
#include <stddef.h>

#include "graph.h"

void initialize_graph(graph *g, bool directed)
{
  int i; /* counter */

  g -> nvertices = 0;
  g -> nedges = 0;
  g -> directed = directed;

  for (i=1; i<=MAXV; i++) g->degree[i] = 0;
  for (i=1; i<=MAXV; i++) g->edges[i] = NULL;
}
