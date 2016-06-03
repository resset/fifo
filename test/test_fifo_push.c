#include <stdint.h>

#include "fifo.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(test_fifo_push);

TEST_SETUP(test_fifo_push)
{
}

TEST_TEAR_DOWN(test_fifo_push)
{
}

TEST(test_fifo_push, test_push_one_byte)
{
    fifo_t fifo;
    const uint16_t SIZE = 5;
    uint8_t buffer[SIZE];

    fifo_init(&fifo, buffer, SIZE);

    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, 0x5A));

    TEST_ASSERT_EQUAL_HEX8(0x5A, fifo.buffer[0]);
}

TEST(test_fifo_push, test_push_fill_buffer)
{
    fifo_t fifo;
    const uint16_t SIZE = 5;
    uint8_t buffer[SIZE];

    fifo_init(&fifo, buffer, SIZE);

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
    fifo_t fifo;
    const uint16_t SIZE = 5;
    uint8_t buffer[SIZE];

    fifo_init(&fifo, buffer, SIZE);

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
        TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push(&fifo, (uint8_t)(i & 0xFF)));
    }

    /* This push should fail. */
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_push(&fifo, 0x0F));

    for (uint16_t i = 0; i < UINT16_MAX; i++) {
        TEST_ASSERT_EQUAL_HEX8((uint8_t)(i & 0xFF), fifo.buffer[i]);
    }
}

TEST(test_fifo_push, test_ef)
{
    fifo_t ef_fifo;
    const uint16_t EF_SIZE = UINT16_MAX;
    uint8_t ef_buffer[EF_SIZE];

    fifo_init(&ef_fifo, ef_buffer, EF_SIZE);

    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_empty(&ef_fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&ef_fifo));

    fifo_push(&ef_fifo, 0);

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&ef_fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&ef_fifo));

    for (uint16_t i = 1; i < EF_SIZE - 1; i++) {
        fifo_push(&ef_fifo, i);
    }

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&ef_fifo));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_full(&ef_fifo));

    fifo_push(&ef_fifo, EF_SIZE - 1);

    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_is_empty(&ef_fifo));
    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_is_full(&ef_fifo));
}
