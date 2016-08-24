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

TEST(test_fifo_empty_full, test_empty_full_basics)
{
    fifo_t * tmp_fifo = NULL;
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_is_empty(tmp_fifo));
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_is_full(tmp_fifo));
}

TEST(test_fifo_empty_full, test_empty_full_small_buffer)
{
    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&fifo));

    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0));

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&fifo));

    for (uint16_t i = 1; i < SIZE - 1; i++) {
        TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, i));
    }

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&fifo));

    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, SIZE - 1));

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_full(&fifo));

    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_push(&fifo, SIZE));

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_full(&fifo));

    uint8_t tmp;
    for (uint16_t i = SIZE; i > 0; i--) {
        TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_pop(&fifo, &tmp));
    }
    (void)tmp;

    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&fifo));
}

TEST(test_fifo_empty_full, test_empty_full_small_buffer_not_from_zero_index)
{
    /* First some dummy pushes. */
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0xA5));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0xB4));

    /* And now we pull data back from the queue. */
    uint8_t tmp;
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_pop(&fifo, &tmp));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_pop(&fifo, &tmp));

    /* Then it's the same as in test_empty_full_small_buffer. */
    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&fifo));

    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0));

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&fifo));

    for (uint16_t i = 1; i < SIZE - 1; i++) {
        TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, i));
    }

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&fifo));

    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, SIZE - 1));

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_full(&fifo));

    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_push(&fifo, SIZE));

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_full(&fifo));

    for (uint16_t i = SIZE; i > 0; i--) {
        TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_pop(&fifo, &tmp));
    }
    (void)tmp;

    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&fifo));
}

TEST(test_fifo_empty_full, test_empty_full_large_buffer)
{
    fifo_t fifo;
    const uint16_t SIZE = UINT16_MAX;
    uint8_t buffer[SIZE];

    if (FIFO_ERROR == fifo_init(&fifo, buffer, SIZE)) {
        TEST_FAIL_MESSAGE("Error while initializing FIFO.");
    }

    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&fifo));

    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0));

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&fifo));

    for (uint16_t i = 1; i < UINT16_MAX - 1; i++) {
        TEST_ASSERT_TRUE(FIFO_SUCCESS ==
                         fifo_push(&fifo, (uint8_t) (i & 0xFF)));
    }

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&fifo));

    TEST_ASSERT_TRUE(FIFO_SUCCESS ==
                     fifo_push(&fifo, (uint8_t) ((UINT16_MAX - 1) & 0xFF)));

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_full(&fifo));

    TEST_ASSERT_TRUE(FIFO_ERROR ==
                     fifo_push(&fifo, (uint8_t) (UINT16_MAX & 0xFF)));

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_full(&fifo));

    uint8_t tmp;
    for (uint16_t i = UINT16_MAX; i > 0; i--) {
        TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_pop(&fifo, &tmp));
    }
    (void)tmp;

    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&fifo));
}

TEST(test_fifo_empty_full, test_empty_full_large_buffer_not_from_zero_index)
{

    fifo_t fifo;
    const uint16_t SIZE = UINT16_MAX;
    uint8_t buffer[SIZE];

    if (FIFO_ERROR == fifo_init(&fifo, buffer, SIZE)) {
        TEST_FAIL_MESSAGE("Error while initializing FIFO.");
    }

    /* First some dummy pushes. */
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0xA5));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0xB4));

    /* And now we pull data back from the queue. */
    uint8_t tmp;
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_pop(&fifo, &tmp));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_pop(&fifo, &tmp));

    /* Then it's the same as in test_empty_full_small_buffer_not_from_zero_index. */
    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&fifo));

    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0));

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&fifo));

    for (uint16_t i = 1; i < UINT16_MAX - 1; i++) {
        TEST_ASSERT_TRUE(FIFO_SUCCESS ==
                         fifo_push(&fifo, (uint8_t) (i & 0xFF)));
    }

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&fifo));

    TEST_ASSERT_TRUE(FIFO_SUCCESS ==
                     fifo_push(&fifo, (uint8_t) ((UINT16_MAX - 1) & 0xFF)));

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_full(&fifo));

    TEST_ASSERT_TRUE(FIFO_ERROR ==
                     fifo_push(&fifo, (uint8_t) (UINT16_MAX & 0xFF)));

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_full(&fifo));

    for (uint16_t i = UINT16_MAX; i > 0; i--) {
        TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_pop(&fifo, &tmp));
    }
    (void)tmp;

    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_empty(&fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&fifo));
}
