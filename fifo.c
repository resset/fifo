#include "fifo.h"

fifo_result_t fifo_init(fifo_t *fifo, uint8_t *buffer, uint16_t size)
{
    (void)fifo;
    (void)buffer;
    (void)size;

    return FIFO_SUCCESS;
}

fifo_result_t fifo_push(fifo_t *fifo, uint8_t data)
{
    (void)fifo;
    (void)data;

    return FIFO_SUCCESS;
}

fifo_result_t fifo_push_multiple(fifo_t *fifo, uint8_t *data, uint16_t size)
{
    (void)fifo;
    (void)data;
    (void)size;

    return FIFO_SUCCESS;
}

uint8_t fifo_pop(fifo_t *fifo)
{
    (void)fifo;

    return FIFO_SUCCESS;
}

uint8_t* fifo_pop_multiple(fifo_t *fifo, uint16_t size)
{
    (void)fifo;
    (void)size;

    return fifo->buffer;
}

fifo_result_t fifo_is_empty(fifo_t *fifo)
{
    (void)fifo;

    return FIFO_SUCCESS;
}

fifo_result_t fifo_is_full(fifo_t *fifo)
{
    (void)fifo;

    return FIFO_SUCCESS;
}

fifo_result_t fifo_search(fifo_t *fifo, uint8_t data)
{
    (void)fifo;
    (void)data;

    return FIFO_SUCCESS;
}
