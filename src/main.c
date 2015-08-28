#include<stdio.h>
#include "graph.h"
#include "bfs.h"

void run_testcase();

graph *gPtr;

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
    graph_ptr = &g;

    initialize_graph(graph_ptr, false);
    initialize_search(graph_ptr);

    scanf("%d", &start_point);

    bfs(graph_ptr, start_point);
}
