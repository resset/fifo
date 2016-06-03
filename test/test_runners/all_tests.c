#include "unity_fixture.h"

static void run_all_tests(void)
{
    RUN_TEST_GROUP(test_fifo_init);
    RUN_TEST_GROUP(test_fifo_push);
    RUN_TEST_GROUP(test_fifo_empty_full);
}

int main(int argc, const char *argv[])
{
    return UnityMain(argc, argv, run_all_tests);
}
