#include "fifo.h"

void fifoInit(fifo_buffer_ptr fifo, uint8_t * memory, const uint16_t size) {
    fifo->index = 0;
    fifo->size = 0;
    fifo->max_size = size;
    fifo->next = 0;
    fifo->data = memory;

    uint16_t i;
    for(i = 0; i < fifo->max_size; i++)
        fifo->data[i] = '\0';
}

uint8_t fifoPush(fifo_buffer_ptr fifo, const uint8_t data) {
    if(fifo->size < fifo->max_size) {
        fifo->data[fifo->next] = data;
        fifo->next++;

        if(fifo->next >= fifo->max_size) fifo->next = 0;

        fifo->size++;

        return FIFO_SUCCESS;
    }
    else
        return FIFO_FULL;
}

uint8_t fifoPop(fifo_buffer_ptr fifo) {
    uint8_t data;

    if(fifo->size > 0) {
        data = fifo->data[fifo->index];
        fifo->index++;

        if(fifo->index >= fifo->max_size) fifo->index = 0;
        fifo->size--;

        return data;
    }
    else
        return FIFO_EMPTY;
}

uint8_t fifoIsFull(fifo_buffer_ptr fifo) {
    return (fifo->size >= fifo->max_size);
}

uint8_t fifoIsEmpty(fifo_buffer_ptr fifo) {
    return (fifo->size == 0);
}
