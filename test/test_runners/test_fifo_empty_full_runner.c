#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(test_fifo_empty_full)
{
    RUN_TEST_CASE(test_fifo_empty_full, test_empty_full_small_fifo);
}
