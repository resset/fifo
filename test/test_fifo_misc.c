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
    fifo_t *tmp_fifo = NULL;
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_find(tmp_fifo, 0));
}

TEST(test_fifo_misc, test_count_elements)
{
}

TEST(test_fifo_misc, test_find)
{
    uint8_t data[] = { 't', 'e', 's', 't', 'i', 'n', 'g', '\n' };

    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push_multiple(&fifo, data, 8));

    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_find(NULL, 0));

    TEST_ASSERT_TRUE(FIFO_TRUE == fifo_find(&fifo, '\n'));
    TEST_ASSERT_TRUE(FIFO_FALSE == fifo_find(&fifo, '\r'));
}

TEST(test_fifo_misc, test_search)
{
    uint8_t data[] = { 't', 'e', 's', 't', 'i', 'n', 'g', '\n' };
    uint8_t pattern[] = { 'i', 'n', 'g' };
    uint8_t long_pattern[] =
        { 't', 'i', 'n', 'g', '\n', 'i', 't', 's', 'l', 'o', 'n', 'g' };
    uint16_t tmp_index;

    TEST_ASSERT_TRUE(FIFO_SUCCESS == fifo_push_multiple(&fifo, data, 8));

    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_search(NULL, NULL, 0, NULL));
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_search(NULL, pattern, 1, NULL));
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_search(&fifo, NULL, 2, NULL));

    /* Search for first byte. */
    TEST_ASSERT_TRUE(FIFO_SUCCESS ==
                     fifo_search(&fifo, (uint8_t *) "t", 1, &tmp_index));
    if (0 != tmp_index) {
        TEST_FAIL();
    }

    /* Search for last byte. */
    TEST_ASSERT_TRUE(FIFO_SUCCESS ==
                     fifo_search(&fifo, (uint8_t *) "\n", 1, &tmp_index));
    if (7 != tmp_index) {
        TEST_FAIL();
    }

    /* Search for middle byte. */
    TEST_ASSERT_TRUE(FIFO_SUCCESS ==
                     fifo_search(&fifo, (uint8_t *) "s", 1, &tmp_index));
    if (2 != tmp_index) {
        TEST_FAIL();
    }

    /* Search for beginning sequence. */
    TEST_ASSERT_TRUE(FIFO_SUCCESS ==
                     fifo_search(&fifo, (uint8_t *) "tes", 3, &tmp_index));
    if (0 != tmp_index) {
        TEST_FAIL();
    }

    /* Search for some middle sequence. */
    TEST_ASSERT_TRUE(FIFO_SUCCESS ==
                     fifo_search(&fifo, (uint8_t *) "es", 2, &tmp_index));
    if (1 != tmp_index) {
        TEST_FAIL();
    }

    /* Search for ending sequence. */
    TEST_ASSERT_TRUE(FIFO_SUCCESS ==
                     fifo_search(&fifo, (uint8_t *) "ting\n", 3, &tmp_index));
    if (3 != tmp_index) {
        TEST_FAIL();
    }

    /* Search for short pattern. */
    TEST_ASSERT_TRUE(FIFO_SUCCESS ==
                     fifo_search(&fifo, pattern, 3, &tmp_index));
    if (4 != tmp_index) {
        TEST_FAIL();
    }

    /* Search for pattern longer than fifo itself shoul fail. */
    TEST_ASSERT_TRUE(FIFO_ERROR == fifo_search(&fifo, long_pattern, 12, NULL));
}
