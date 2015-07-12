#ifndef __FIFO_H__
#define __FIFO_H__

#include <inttypes.h>

typedef struct __fifo_buffer fifo_buffer_t;
typedef fifo_buffer_t * fifo_buffer_ptr;

struct __fifo_buffer {
    // used for read data
    uint16_t index;

    // used for write data
    uint16_t next;

    // now size
    uint16_t size;

    // max size of memory in bytes
    uint16_t max_size;

    // memory of buffer
    uint8_t * data;
};

#define FIFO_SUCCESS        0
#define FIFO_FAILURE        1
#define FIFO_FULL           2
#define FIFO_EMPTY          3

#define FIFO_YES            1
#define FIFO_NO             !FIFO_YES

/**
 * Initialize the buffer pointer with size
 * @param fifo poniter for buffer information
 * @param memory
 * @param size size of memory in buffer
 */
void fifo_init(fifo_buffer_ptr fifo, uint8_t * memory, const uint16_t size);

/**
 * push data in buffer memory
 * @param fifo poniter for buffer information
 * @param data byte to store in buffer memory
 * @return FIFO_SUCCESS when data is stored or FIFO_FULL if memory is full.
 */
uint8_t fifo_push(fifo_buffer_ptr fifo, const uint8_t data);

/**
 * pop data of memory
 * @param fifo poniter for buffer information
 * @return data in memory or FIFO_EMPTY if memory data is empty
 */
uint8_t fifo_pop(fifo_buffer_ptr fifo);

/**
 * check if memory data is full
 * @param fifo poniter for buffer information
 * @return FIFO_YES if memory is full or FIFO_NO.
 */
uint8_t fifo_is_full(fifo_buffer_ptr fifo);

/**
 * check if memory data is empty
 * @param fifo poniter for buffer information
 * @return FIFO_YES if memory data is empty of FIFO_NO.
 */
uint8_t fifo_is_empty(fifo_buffer_ptr fifo);

#endif
