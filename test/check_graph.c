#include <stdio.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "graph.h"

/* Pointer to the file used by the tests. */
static FILE* temp_file = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void)
{
        return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
        return 0;
}

void test_stdin(void)
{
        char c;
        freopen("test/fixtures/test1.txt", "r", stdin);
        c = getchar();
        CU_ASSERT(c == '1');
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
        if (NULL == CU_add_test(pSuite, "test of test_stdin()", test_stdin))
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
