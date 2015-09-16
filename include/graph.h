#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#define MAXV 1000 /* Maximum number of nodes */
#define MAXINT 1000 /* Maximum length between two nodes */

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

void initialize_graph(graph *g, bool directed);
void read_graph(graph *g, bool directed);

#endif
