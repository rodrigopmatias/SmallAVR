#include "utask.h"

static uint8_t start_ovf = 0;

static task_t * __fifo[UTASK_FIFO_SIZE];

ISR(TIMER0_OVF_vect) {
    static uint8_t ovf_counter = 0;
    uint8_t idx;

    ovf_counter++;
    TCNT = start_ovf;

    if(ovf_counter == UTASK_OVF_SIZE) {
        ovf_counter = 0;
        for(idx = 0; idx < UTASK_FIFO_SIZE; idx++)
            if(__fifo[idx]->fn) __fifo[idx]->fn();
    }
}

void utaskConfigure(void) {
    cli();
    if(F_CPU == 16000000UL) {
        start_ovf = 5;
        TCCR = (1 << CS01) | (1 << CS00);
    }
    else if(F_CPU == 8000000UL) {
        start_ovf = 130;
        TCCR = (1 << CS01) | (1 << CS00);
    }
    else if(F_CPU == 1000000UL) {
        start_ovf = 130;
        TCCR = (1 << CS01);
    }

    TIMSK = (1 << TOIE0);

    TCNT = start_ovf;
    sei();

    uint8_t index;
    task_t * task;

    for(index = 0; index < UTASK_FIFO_SIZE;index++) {
        task = (task_t *)malloc(sizeof(task_t));
        task->fn = 0;

        __fifo[index] = task;
    }
}

void utaskRegister(const uint8_t position, void (* fn)(void)) {
    task_t * task;

    if(position < UTASK_FIFO_SIZE) {
        task = __fifo[position];
        free(task);

        task = (task_t *)malloc(sizeof(task_t));
        task->fn = fn;

        __fifo[position] = task;
    }
}
