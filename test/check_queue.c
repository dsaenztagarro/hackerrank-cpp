#include <stdio.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "queue.h"

/* Pointer to the file used by the tests. */
static FILE* temp_file = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void)
{
   if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
      return -1;
   }
   else {
      return 0;
   }
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
   if (0 != fclose(temp_file)) {
      return -1;
   }
   else {
      temp_file = NULL;
      return 0;
   }
}

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

void test_init_queue(void)
{
        queue *qptr = init_queue_with(NULL);
        CU_ASSERT(qptr->first == NULL);
        CU_ASSERT(qptr->last == NULL);
}

void test_enqueue_empty_queue(void)
{
        int items[] = { 5, 0 };
        queue *qptr = init_queue_with(items);
        CU_ASSERT(qptr->first->item == 5);
        CU_ASSERT(qptr->last->item == 5);
}

void test_enqueue_non_empty_queue(void)
{
        int items[] = { 5, 12, 0 };
        queue *qptr = init_queue_with(items);
        CU_ASSERT(qptr->first->item == 5);
        CU_ASSERT(qptr->last->item == 12);
}

void test_dequeue(void)
{
        int items[] = { 5, 10, 15, 0 };
        queue *qptr = init_queue_with(items);
        CU_ASSERT(qptr->first->item == 5);
        dequeue(qptr);
        CU_ASSERT(qptr->first->item == 10);
}

void test_empty_queue(void)
{
        queue *qptr = init_queue_with(NULL);
        CU_ASSERT(1 == empty_queue(qptr));
}

void test_non_empty_queue(void)
{
        int items[] = { 5 };
        queue *qptr = init_queue_with(items);
        CU_ASSERT(0 == empty_queue(qptr));
}

int main(void)
{
        CU_pSuite pSuite = NULL;

        /* initialize the CUnit test registry */
        if (CUE_SUCCESS != CU_initialize_registry())
                return CU_get_error();

        /* add a suite to the registry */
        pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
        if (NULL == pSuite) {
                CU_cleanup_registry();
                return CU_get_error();
        }

        /* add the tests to the suite */
        /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
        if ((NULL == CU_add_test(pSuite, "test of init_queue()", test_init_queue)) ||
                (NULL == CU_add_test(pSuite, "test empty of enqueue()", test_enqueue_empty_queue)) ||
                (NULL == CU_add_test(pSuite, "test non empty of enqueue()", test_enqueue_non_empty_queue)) ||
                (NULL == CU_add_test(pSuite, "test of dequeue()", test_dequeue)) ||
                (NULL == CU_add_test(pSuite, "test of empty_queue()", test_empty_queue)) ||
                (NULL == CU_add_test(pSuite, "test of empty_queue()", test_non_empty_queue)))
        {
                CU_cleanup_registry();
                return CU_get_error();
        }

        /* Run all tests using the CUnit Basic interface */
        CU_basic_set_mode(CU_BRM_VERBOSE);
        CU_basic_run_tests();
        CU_cleanup_registry();
        return CU_get_error();
}
