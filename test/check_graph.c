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
#include <check.h>
#include "graph.h"

START_TEST(test_stdin)
{
        char c;
        freopen("test/fixtures/test1.txt", "r", stdin);
        c = getchar();
        ck_assert_int_eq(c, '1');
}
END_TEST

Suite * make_graph_suite(void)
{
        Suite *s1 = suite_create("Graph");
        TCase *tc1_1 = tcase_create("graph#test_stdin");
        suite_add_tcase(s1, tc1_1);
        tcase_add_test(tc1_1, test_stdin);
        return s1;
}
