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
#include "main.h"
#include "graph.h"
#include "dijkstra.h"

void run_testcase();
void init_distances(int start_point);
void print_distances(graph * g, int start_point);
void print_distances_interval(int start, int end, int start_point, int *first);

graph *gPtr;
int distances[MAXV + 1];

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
        read_graph(graphptr, false, true);

        scanf("%d", &start_point);

        dijkstra(graphptr, start_point);
        print_distances(graphptr, start_point);
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
