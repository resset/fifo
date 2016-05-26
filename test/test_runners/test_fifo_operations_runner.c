#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(fifo_operations)
{
    RUN_TEST_CASE(fifo_operations, test_push_one_byte);
    RUN_TEST_CASE(fifo_operations, test_push_fill_buffer);
    RUN_TEST_CASE(fifo_operations, test_push_overfill_buffer);
//     RUN_TEST_CASE(fifo_operations, test_push_overfill_large_buffer);
}
