#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(test_fifo_pop)
{
    RUN_TEST_CASE(test_fifo_pop, test_pop_basics);
    RUN_TEST_CASE(test_fifo_pop, test_pop_one_byte);
    RUN_TEST_CASE(test_fifo_pop, test_pop_full_buffer);
    RUN_TEST_CASE(test_fifo_pop, test_pop_multiple_basics);
    RUN_TEST_CASE(test_fifo_pop, test_pop_multiple);
    RUN_TEST_CASE(test_fifo_pop, test_pop_multiple_more_than_empty);
}
