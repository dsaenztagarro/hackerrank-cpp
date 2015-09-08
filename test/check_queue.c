#include <check.h>
#include "queue.h"

Queueptr queuealloc(void)
{
        return (Queueptr)malloc(sizeof(queue));
}

Queueptr init_queue_with(int *items)
{
        queue *qptr = queuealloc();
        init_queue(qptr);
        if (items)
                for (; *items; items++)
                        enqueue(qptr, *items);
        return qptr;
}

START_TEST(test_init_queue)
{
        queue *qptr = init_queue_with(NULL);
        ck_assert_ptr_eq(qptr->first, NULL);
        ck_assert_ptr_eq(qptr->last, NULL);
}
END_TEST

START_TEST(test_enqueue_empty_queue)
{
        int items[] = { 5, 0 };
        queue *qptr = init_queue_with(items);
        ck_assert_int_eq(qptr->first->item, 5);
        ck_assert_int_eq(qptr->last->item, 5);
}
END_TEST

START_TEST(test_enqueue_non_empty_queue)
{
        int items[] = { 5, 12, 0 };
        queue *qptr = init_queue_with(items);
        ck_assert_int_eq(qptr->first->item, 5);
        ck_assert_int_eq(qptr->last->item, 12);
}
END_TEST

START_TEST(test_dequeue)
{

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
        tcase_add_test(tc1_1, test_enqueue_empty_queue);
        tcase_add_test(tc1_1, test_enqueue_non_empty_queue);

        srunner_run_all(sr, CK_ENV);
        nf = srunner_ntests_failed(sr);
        srunner_free(sr);

        return nf == 0 ? 0 : 1;
        return 0;
}
