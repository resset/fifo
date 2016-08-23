#include <stdint.h>

#include "fifo.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(test_fifo_init);

static fifo_t fifo;
static const uint16_t SIZE = UINT16_MAX;
static uint8_t buffer[UINT16_MAX];

TEST_SETUP(test_fifo_init)
{
}

TEST_TEAR_DOWN(test_fifo_init)
{
}

TEST(test_fifo_init, test_basic_asserts)
{
    TEST_ASSERT_FALSE(FIFO_TRUE == FIFO_FALSE);
    TEST_ASSERT_FALSE(FIFO_SUCCESS == FIFO_ERROR);

    TEST_ASSERT_TRUE(FIFO_TRUE != FIFO_SUCCESS);
    TEST_ASSERT_TRUE(FIFO_FALSE != FIFO_ERROR);
}

TEST(test_fifo_init, test_fifo_init_errors)
{
    /* Initialization errors. */
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_init(NULL, buffer, SIZE));
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_init(&fifo, NULL, SIZE));
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_init(&fifo, buffer, 0));
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_init(NULL, NULL, 0));

    /* Other random initialization errors. */
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_init(&fifo, 0, SIZE));
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_init(0, buffer, SIZE));
}

TEST(test_fifo_init, test_fifo_init_successes)
{
    /* Now some positive tests. */
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_init(&fifo, buffer, SIZE));
    TEST_ASSERT_NOT_NULL(fifo.buffer);
    TEST_ASSERT_TRUE(buffer == fifo.buffer);
    TEST_ASSERT_EQUAL_UINT16(SIZE, fifo.size);
    TEST_ASSERT_EQUAL_UINT16(0, fifo.first);
    TEST_ASSERT_EQUAL_UINT16(0, fifo.elements_n);

    /* Multiple initialization is not an error. */
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_init(&fifo, buffer, SIZE / 2));
    TEST_ASSERT_EQUAL_UINT16(SIZE / 2, fifo.size);

    /* -1 will be casted to uint16_t and will result in 65535
     * which is correct value.
     */
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_init(&fifo, buffer, -1));

    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_init(&fifo, buffer, UINT16_MAX));
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_init(&fifo, buffer, INT8_MIN));
}
