#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(test_fifo_push)
{
    RUN_TEST_CASE(test_fifo_push, test_push_one_byte);
    RUN_TEST_CASE(test_fifo_push, test_push_fill_buffer);
    RUN_TEST_CASE(test_fifo_push, test_push_overfill_buffer);
    RUN_TEST_CASE(test_fifo_push, test_push_overfill_large_buffer);
    RUN_TEST_CASE(test_fifo_push, test_push_fill_buffer_not_from_zero_index);
}
