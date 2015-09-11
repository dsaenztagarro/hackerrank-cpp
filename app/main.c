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
    printf("num_testcases %d\n", num_testcases);
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
    read_graph(graphptr, false);
    initialize_search(graphptr);

    scanf("%d", &start_point);
    printf("start point %d\n", start_point);

    bfs(graphptr, start_point);
}
