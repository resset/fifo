#include <stdint.h>

#include "fifo.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(test_fifo_misc);

static fifo_t fifo;
static const uint16_t SIZE = 5;
static uint8_t buffer[5];

TEST_SETUP(test_fifo_misc)
{
    if (FIFO_ERROR == fifo_init(&fifo, buffer, SIZE)) {
        TEST_FAIL_MESSAGE("Error while initializing FIFO.");
    }
}

TEST_TEAR_DOWN(test_fifo_misc)
{
}

TEST(test_fifo_misc, test_misc_basics)
{
    fifo_t * tmp_fifo = NULL;
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_search(tmp_fifo, 0));
}

TEST(test_fifo_misc, test_count_elements)
{
}

TEST(test_fifo_misc, test_find)
{
}

TEST(test_fifo_misc, test_search)
{
}
