# include <inttypes.h>
# include <stdio.h>

#include "../../fifo.h"

int main(void)
{
    fifo_t fifo;
    const uint16_t FIFO_SIZE = 5;
    uint8_t buffer[FIFO_SIZE];

    if (FIFO_SUCCESS == fifo_init(&fifo, buffer, FIFO_SIZE)) {

        for (uint16_t i = 0; i < 7; ++i) {
            if (FIFO_SUCCESS == fifo_push(&fifo, i + 1)) {
                printf("Added: %d\n", i + 1);
            } else {
                printf("Not added: %d\n", i + 1);
            }
        }
        printf("No. of elements: %d\n", fifo_count_elements(&fifo));
        while (FIFO_FALSE == fifo_is_empty(&fifo)) {
            printf("Removed: %d\n", fifo_pop(&fifo));
        }
        printf("\n");

        for (uint16_t i = 0; i < 3; ++i) {
            if (FIFO_SUCCESS == fifo_push(&fifo, i + 1)) {
                printf("Added: %d\n", i + 1);
            } else {
                printf("Not added: %d\n", i + 1);
            }
        }
        printf("No. of elements: %d\n", fifo_count_elements(&fifo));
        while (FIFO_FALSE == fifo_is_empty(&fifo)) {
            printf("Removed: %d\n", fifo_pop(&fifo));
        }
        printf("\n");

        for (uint16_t i = 0; i < 5; ++i) {
            if (FIFO_SUCCESS == fifo_push(&fifo, i + 1)) {
                printf("Added: %d\n", i + 1);
            } else {
                printf("Not added: %d\n", i + 1);
            }
        }
        printf("No. of elements: %d\n", fifo_count_elements(&fifo));
        while (FIFO_FALSE == fifo_is_empty(&fifo)) {
            printf("Removed: %d\n", fifo_pop(&fifo));
        }
        printf("\n");

    } else {
        printf("Cannot initialize FIFO.\n");
    }

    return 0;
}
