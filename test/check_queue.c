#include <stdio.h>
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
        int items[] = { 5, 10, 15, 0 };
        queue *qptr = init_queue_with(items);
        ck_assert_int_eq(qptr->first->item, 5);
        dequeue(qptr);
        ck_assert_int_eq(qptr->first->item, 10);
}
END_TEST

START_TEST(test_empty_queue)
{
        queue *qptr = init_queue_with(NULL);
        ck_assert_int_eq(1, empty_queue(qptr));
}
END_TEST

START_TEST(test_non_empty_queue)
{
        int items[] = { 5 };
        queue *qptr = init_queue_with(items);
        ck_assert_int_eq(0, empty_queue(qptr));
}
END_TEST

int main(void)
{
        Suite *s1 = suite_create("Queue");
        TCase *tc1_1 = tcase_create("queue#init_queue");
        TCase *tc1_2 = tcase_create("queue#enqueue");
        TCase *tc1_3 = tcase_create("queue#dequeue");
        TCase *tc1_4 = tcase_create("queue#empty_queue");
        SRunner *sr = srunner_create(s1);
        int nf;

        suite_add_tcase(s1, tc1_1);
        suite_add_tcase(s1, tc1_2);
        suite_add_tcase(s1, tc1_3);
        suite_add_tcase(s1, tc1_4);

        tcase_add_test(tc1_1, test_init_queue);
        tcase_add_test(tc1_2, test_enqueue_empty_queue);
        tcase_add_test(tc1_2, test_enqueue_non_empty_queue);
        tcase_add_test(tc1_3, test_dequeue);
        tcase_add_test(tc1_4, test_empty_queue);
        tcase_add_test(tc1_4, test_non_empty_queue);

        srunner_run_all(sr, CK_ENV);
        nf = srunner_ntests_failed(sr);
        srunner_free(sr);

        return nf == 0 ? 0 : 1;
        return 0;
}
