#include "utask.h"

static uint8_t start_ovf = 0;

static task_t __queue[UTASK_QUEUE_SIZE];

ISR(TIMER0_OVF_vect) {
    static uint8_t ovf_counter = 0;
    uint8_t idx;

    ovf_counter++;
    TCNT = start_ovf;

    if(ovf_counter == UTASK_OVF_SIZE) {
        cli();
        ovf_counter = 0;
        for(idx = 0; idx < UTASK_QUEUE_SIZE; idx++)
            if(__queue[idx].fn) __queue[idx].fn();
        sei();
    }
}

void utaskConfigure(void) {
    uint8_t idx;

    cli();
    #if F_CPU == 16000000UL
    start_ovf = 5;
    TCCR = (1 << CS01) | (1 << CS00);
    #elif F_CPU == 8000000UL
    start_ovf = 130;
    TCCR = (1 << CS01) | (1 << CS00);
    #elif F_CPU == 4000000UL
    start_ovf = 193;
    TCCR = (1 << CS01) | (1 << CS00);
    #elif F_CPU == 1000000UL
    start_ovf = 130;
    TCCR = (1 << CS01);
    #endif
    TIMSK = (1 << TOIE0);
    TCNT = start_ovf;
    sei();

    for(idx = 0; idx < UTASK_QUEUE_SIZE;idx++)
        __queue[idx].fn = 0;
}

void utaskRegister(const uint8_t position, void (* fn)(void)) {
    if(position < UTASK_QUEUE_SIZE) {
        __queue[position].fn = fn;
    }
}
