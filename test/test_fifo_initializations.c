#include <inttypes.h>

#include "fifo.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(fifo_initializations);

static fifo_t fifo;
static const uint16_t SIZE = UINT16_MAX;
static uint8_t buffer[UINT16_MAX];

TEST_SETUP(fifo_initializations)
{
}

TEST_TEAR_DOWN(fifo_initializations)
{
}

TEST(fifo_initializations, test_basics)
{
    TEST_ASSERT_FALSE(FIFO_TRUE == FIFO_FALSE);
    TEST_ASSERT_FALSE(FIFO_SUCCESS == FIFO_ERROR);
}

TEST(fifo_initializations, test_fifo_init)
{
    /* Initialization errors. */
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_init(NULL, buffer, SIZE));
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_init(&fifo, NULL, SIZE));
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_init(&fifo, buffer, 0));
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_init(NULL, NULL, 0));

    /* Random initialization errors. */
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_init(&fifo, 0, SIZE));
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_init(0, buffer, SIZE));

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
