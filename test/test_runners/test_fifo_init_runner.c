#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(test_fifo_init)
{
    RUN_TEST_CASE(test_fifo_init, test_basic_asserts);
    RUN_TEST_CASE(test_fifo_init, test_fifo_init);
}
