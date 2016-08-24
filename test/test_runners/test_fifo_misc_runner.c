#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(test_fifo_misc)
{
    RUN_TEST_CASE(test_fifo_misc, test_misc_basics);
    RUN_TEST_CASE(test_fifo_misc, test_count_elements);
    RUN_TEST_CASE(test_fifo_misc, test_search);
}
