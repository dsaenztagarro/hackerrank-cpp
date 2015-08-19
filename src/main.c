#include<stdio.h>
#include "graph.h"

graph *gPtr;

int main()
{
    graph g;
    gPtr = &g;
    printf("Hello World");
    initialize_graph(gPtr, false);
		return 0;
}
