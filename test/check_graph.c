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
