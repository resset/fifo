#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(test_fifo_push)
{
    RUN_TEST_CASE(test_fifo_push, test_push_basics);
    RUN_TEST_CASE(test_fifo_push, test_push_one_byte);
    RUN_TEST_CASE(test_fifo_push, test_push_fill_buffer);
    RUN_TEST_CASE(test_fifo_push, test_push_overfill_buffer);
    RUN_TEST_CASE(test_fifo_push, test_push_overfill_large_buffer);
    RUN_TEST_CASE(test_fifo_push, test_push_fill_buffer_not_from_zero_index);
    RUN_TEST_CASE(test_fifo_push, test_push_multiple_basics);
    RUN_TEST_CASE(test_fifo_push, test_push_multiple);
    RUN_TEST_CASE(test_fifo_push, test_push_multiple_overfill_buffer_when_full);
    RUN_TEST_CASE(test_fifo_push,
                  test_push_multiple_overfill_buffer_when_almost_full);
}
