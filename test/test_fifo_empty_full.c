#include <stdint.h>

#include "fifo.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(test_fifo_empty_full);

static fifo_t fifo;
static const uint16_t SIZE = 5;
static uint8_t buffer[5];

TEST_SETUP(test_fifo_empty_full)
{
    if (FIFO_ERROR == fifo_init(&fifo, buffer, SIZE)) {
        TEST_FAIL_MESSAGE("Error while initializing FIFO.");
    }
}

TEST_TEAR_DOWN(test_fifo_empty_full)
{
}

TEST(test_fifo_empty_full, test_empty_full_small_fifo)
{
    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&fifo));

    fifo_push(&fifo, 0);

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&fifo));

    for (uint16_t i = 1; i < SIZE - 1; i++) {
        fifo_push(&fifo, i);
    }

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&fifo));

    fifo_push(&fifo, SIZE - 1);

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_full(&fifo));

    fifo_push(&fifo, SIZE);

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_full(&fifo));

    for (uint16_t i = SIZE; i > 0; i--) {
        fifo_pop(&fifo);
    }

    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&fifo));
}
