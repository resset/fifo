#include <inttypes.h>

#include "fifo.h"
#include "unity.h"
#include "test.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_fifo_init(void)
{
    fifo_t fifo;
    const uint16_t SIZE = UINT16_MAX;
    uint8_t buffer[SIZE];

    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_init(NULL, buffer, SIZE));
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_init(&fifo, NULL, SIZE));
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_init(&fifo, buffer, 0));
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_init(NULL, NULL, 0));

    /* Random errors. */
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_init(&fifo, 0, SIZE));
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_init(0, buffer, SIZE));

    /* -1 will be casted to uint16_t and will result in 65535
     * which is perfectly correct value.
     */
    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_init(&fifo, buffer, -1));

    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_init(&fifo, buffer, SIZE));
    TEST_ASSERT_NOT_NULL(fifo.buffer);
    TEST_ASSERT_EQUAL_UINT16(SIZE, fifo.size);
    TEST_ASSERT_EQUAL_UINT16(0, fifo.first);
    TEST_ASSERT_EQUAL_UINT16(0, fifo.elements_n);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_fifo_init);
    return UNITY_END();
}
