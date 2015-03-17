#ifndef __UTASK_H__
#define __UTASK_H__

#include <stdint.h>
#include <avr/interrupt.h>
#include "utask_compat.h"

#ifndef UTASK_QUEUE_SIZE
#define UTASK_QUEUE_SIZE         5U
#endif

#ifndef UTASK_OVF_SIZE
#define UTASK_OVF_SIZE          25U
#endif

#define millis(ms)              ms / UTASK_OVF_SIZE

typedef struct {
    void (* fn)(void);
} task_t;

/**
 * This function configure the clock and prepare the __fifo of tasks to run the
 * tasks.
 **/
void utaskConfigure(void);

/**
 * This function register the function fn in __fifo for run in the task enviroment.
 * @param position, the position of task in the __fifo
 * @param fn, the function that define task.
 **/
void utaskRegister(const uint8_t position, void (* fn)(void));

#endif /* __UTASK_H__ */