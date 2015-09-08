#include <check.h>
#include "queue.h"

START_TEST(test_init_queue)
{
        queue q;
        queue *qptr;
        qptr = &q;
        init_queue(qptr);
        ck_assert_ptr_eq(qptr->first, NULL);
        ck_assert_ptr_eq(qptr->last, NULL);
}
END_TEST

int main(void)
{
        Suite *s1 = suite_create("Core");
        TCase *tc1_1 = tcase_create("Core");
        SRunner *sr = srunner_create(s1);
        int nf;

        suite_add_tcase(s1, tc1_1);
        tcase_add_test(tc1_1, test_init_queue);

        srunner_run_all(sr, CK_ENV);
        nf = srunner_ntests_failed(sr);
        srunner_free(sr);

        return nf == 0 ? 0 : 1;
        return 0;
}
