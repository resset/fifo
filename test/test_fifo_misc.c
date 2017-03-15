#include <stdint.h>

#include "fifo.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(test_fifo_misc);

static fifo_t fifo;
static const uint16_t SIZE = 10;
static uint8_t buffer[10];

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
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_find(tmp_fifo, 0));
}

TEST(test_fifo_misc, test_count_elements)
{
}

TEST(test_fifo_misc, test_find)
{
    uint8_t data[] = {'t', 'e', 's', 't', 'i', 'n', 'g', '\n'};

    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push_multiple(&fifo, data, 8));

    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_find(NULL, 0));

    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_find(&fifo, '\n'));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_find(&fifo, '\r'));
}

TEST(test_fifo_misc, test_search)
{
}
