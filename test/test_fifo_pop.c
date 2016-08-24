#include <stdint.h>

#include "fifo.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(test_fifo_pop);

static fifo_t fifo;
static const uint16_t SIZE = 5;
static uint8_t buffer[5];

TEST_SETUP(test_fifo_pop)
{
    if (FIFO_ERROR == fifo_init(&fifo, buffer, SIZE)) {
        TEST_FAIL_MESSAGE("Error while initializing FIFO.");
    }
}

TEST_TEAR_DOWN(test_fifo_pop)
{
}

TEST(test_fifo_pop, test_pop_basics)
{
    fifo_t * tmp_fifo = NULL;
    uint8_t * tmp_data = NULL;
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_pop(tmp_fifo, tmp_data));
}

TEST(test_fifo_pop, test_pop_one_byte)
{
    const uint8_t test_value = 0x5A;

    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, test_value));

    uint8_t data;
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_pop(&fifo, &data));

    TEST_ASSERT_EQUAL_HEX8(test_value, data);
}

TEST(test_fifo_pop, test_pop_full_buffer)
{
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x5A));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x4B));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x3C));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x2D));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x1E));

    uint8_t data[5];
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_pop(&fifo, &data[0]));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_pop(&fifo, &data[1]));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_pop(&fifo, &data[2]));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_pop(&fifo, &data[3]));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_pop(&fifo, &data[4]));

    TEST_ASSERT_EQUAL_HEX8(0x5A, data[0]);
    TEST_ASSERT_EQUAL_HEX8(0x4B, data[1]);
    TEST_ASSERT_EQUAL_HEX8(0x3C, data[2]);
    TEST_ASSERT_EQUAL_HEX8(0x2D, data[3]);
    TEST_ASSERT_EQUAL_HEX8(0x1E, data[4]);

    /* This should fail and shouldn't change data value. */
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_pop(&fifo, &data[0]));

    TEST_ASSERT_EQUAL_HEX8(0x5A, data[0]);
    TEST_ASSERT_EQUAL_HEX8(0x4B, data[1]);
    TEST_ASSERT_EQUAL_HEX8(0x3C, data[2]);
    TEST_ASSERT_EQUAL_HEX8(0x2D, data[3]);
    TEST_ASSERT_EQUAL_HEX8(0x1E, data[4]);
}

TEST(test_fifo_pop, test_pop_multiple_basics)
{
    fifo_t * tmp_fifo = NULL;
    uint8_t * tmp_data = NULL;
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_pop_multiple(tmp_fifo, tmp_data, 1));
}

TEST(test_fifo_pop, test_pop_multiple)
{
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x5A));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x4B));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x3C));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x2D));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x1E));

    uint8_t data[5];
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_pop_multiple(&fifo, data, 5));
}
