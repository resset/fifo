# include <inttypes.h>
# include <stdio.h>

#include "../fifo.h"

int main(void)
{
    fifo_t fifo;
    const uint16_t FIFO_SIZE = 13;
    uint8_t buffer[FIFO_SIZE];

    fifo_init(&fifo, buffer, FIFO_SIZE);

    return 0;
}
