#ifndef __UTASK_H__
#define __UTASK_H__

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#if defined(__AVR_ATmega640__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || \
    defined(__AVR_ATmega48P__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328P__)
#define TCCR                    TCCR0B
#define TIMSK                   TIMSK0
#define TCNT                    TCNT0
#elif defined(__AVR_ATmega8__)
#define TCCR                    TCCR0
#define TCNT                    TCNT0
#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
#define TCCR                    TCCR0B
#define TCNT                    TCNT0
#endif

#ifndef UTASK_FIFO_SIZE
#define UTASK_FIFO_SIZE         5U
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