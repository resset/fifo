#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(fifo_initializations)
{
    RUN_TEST_CASE(fifo_initializations, test_basics);
    RUN_TEST_CASE(fifo_initializations, test_fifo_init);
}
