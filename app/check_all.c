#include <stdio.h>
#include <check.h>
#include "check_graph.h"
#include "check_queue.h"

int main(void)
{
        int nf;

        Suite *s0 = suite_create("Master");

        SRunner *sr = srunner_create(s0);
        srunner_add_suite (sr, make_graph_suite());
        srunner_add_suite (sr, make_queue_suite());

        srunner_run_all(sr, CK_ENV);
        nf = srunner_ntests_failed(sr);
        srunner_free(sr);

        return nf == 0 ? 0 : 1;
        return 0;
}
