#ifndef __UTASK_H__
#define __UTASK_H__

#include <stdint.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#if defined(__AVR_ATmega640__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || \
    defined(__AVR_ATmega48P__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328P__)
#define TCCR                    TCCR0B
#define TIMSK                   TIMSK0
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

void utaskConfigure(void);
void utaskRegister(const uint8_t position, void (* fn)(void));

#endif /* __UTASK_H__ */