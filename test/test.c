# include <inttypes.h>
# include <stdio.h>

#include "../fifo.h"

int main(void)
{
    fifo_t fifo;
    const uint16_t FIFO_SIZE = 5;
    uint8_t buffer[FIFO_SIZE];

    fifo_init(&fifo, buffer, FIFO_SIZE);

    fifo_push(&fifo, 0x1);
    fifo_push(&fifo, 0x2);
    fifo_push(&fifo, 0x3);
    fifo_push(&fifo, 0x4);
    fifo_push(&fifo, 0x5);
    while (FIFO_FALSE == fifo_is_empty(&fifo)) {
        printf("Element: %d\n", fifo_pop(&fifo));
    }
    printf("\n");

    fifo_push(&fifo, 0x1);
    fifo_push(&fifo, 0x2);
    fifo_push(&fifo, 0x3);
    fifo_push(&fifo, 0x4);
    fifo_push(&fifo, 0x5);
    while (FIFO_FALSE == fifo_is_empty(&fifo)) {
        printf("Element: %d\n", fifo_pop(&fifo));
    }
    printf("\n");

    fifo_push(&fifo, 0x1);
    fifo_push(&fifo, 0x2);
    fifo_push(&fifo, 0x3);
    fifo_push(&fifo, 0x4);
    fifo_push(&fifo, 0x5);
    while (FIFO_FALSE == fifo_is_empty(&fifo)) {
        printf("Element: %d\n", fifo_pop(&fifo));
    }

    return 0;
}
