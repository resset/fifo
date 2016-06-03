#include <stdint.h>

#include "fifo.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(test_fifo_push);

static fifo_t fifo;
static const uint16_t SIZE = 5;
static uint8_t buffer[5];

TEST_SETUP(test_fifo_push)
{
    if (FIFO_ERROR == fifo_init(&fifo, buffer, SIZE)) {
        TEST_FAIL_MESSAGE("Error while initializing FIFO.");
    }
}

TEST_TEAR_DOWN(test_fifo_push)
{
}

TEST(test_fifo_push, test_push_one_byte)
{
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x5A));

    TEST_ASSERT_EQUAL_HEX8(0x5A, fifo.buffer[0]);
}

TEST(test_fifo_push, test_push_fill_buffer)
{
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x5A));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x4B));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x3C));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x2D));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x1E));

    TEST_ASSERT_EQUAL_HEX8(0x5A, fifo.buffer[0]);
    TEST_ASSERT_EQUAL_HEX8(0x4B, fifo.buffer[1]);
    TEST_ASSERT_EQUAL_HEX8(0x3C, fifo.buffer[2]);
    TEST_ASSERT_EQUAL_HEX8(0x2D, fifo.buffer[3]);
    TEST_ASSERT_EQUAL_HEX8(0x1E, fifo.buffer[4]);
}

TEST(test_fifo_push, test_push_overfill_buffer)
{
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x5A));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x4B));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x3C));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x2D));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x1E));

    /* This push should fail. */
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_push(&fifo, 0x0F));

    TEST_ASSERT_EQUAL_HEX8(0x5A, fifo.buffer[0]);
    TEST_ASSERT_EQUAL_HEX8(0x4B, fifo.buffer[1]);
    TEST_ASSERT_EQUAL_HEX8(0x3C, fifo.buffer[2]);
    TEST_ASSERT_EQUAL_HEX8(0x2D, fifo.buffer[3]);
    TEST_ASSERT_EQUAL_HEX8(0x1E, fifo.buffer[4]);
}

TEST(test_fifo_push, test_push_overfill_large_buffer)
{
    fifo_t fifo;
    const uint16_t SIZE = UINT16_MAX;
    uint8_t buffer[SIZE];

    if (FIFO_ERROR == fifo_init(&fifo, buffer, SIZE)) {
        TEST_FAIL_MESSAGE("Error while initializing FIFO.");
    }

    for (uint16_t i = 0; i < UINT16_MAX; i++) {
        TEST_ASSERT_TRUE(FIFO_SUCCESS ==
                         fifo_push(&fifo, (uint8_t) (i & 0xFF)));
    }

    /* These pushes should fail. */
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_push(&fifo, 0x0F));
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_push(&fifo, 0x1F));
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_push(&fifo, 0x2F));

    for (uint16_t i = 0; i < UINT16_MAX; i++) {
        TEST_ASSERT_EQUAL_HEX8((uint8_t) (i & 0xFF), fifo.buffer[i]);
    }
}

TEST(test_fifo_push, test_push_fill_buffer_not_from_zero_index)
{
    /* First some dummy pushes. */
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x5A));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x4B));

    /* And now we pull data back from the queue. */
    uint8_t tmp;
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_pop(&fifo, &tmp));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_pop(&fifo, &tmp));
    (void)tmp;

    /* We still should have 5 empty places albeit not starting from index 0. */
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x5A));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x4B));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x3C));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x2D));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x1E));

    /* This push should fail. */
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_push(&fifo, 0x0F));

    /* Now we start from third element. */
    TEST_ASSERT_EQUAL_HEX8(0x5A, fifo.buffer[2]);
    TEST_ASSERT_EQUAL_HEX8(0x4B, fifo.buffer[3]);
    TEST_ASSERT_EQUAL_HEX8(0x3C, fifo.buffer[4]);
    TEST_ASSERT_EQUAL_HEX8(0x2D, fifo.buffer[0]);
    TEST_ASSERT_EQUAL_HEX8(0x1E, fifo.buffer[1]);
}
