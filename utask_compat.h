#ifndef __UTASK_COMPAT_H__
#define __UTASK_COMPAT_H__

#include <avr/io.h>

#if defined(__AVR_ATmega640__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || \
    defined(__AVR_ATmega48P__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168P__) || \
    defined(__AVR_ATmega328P__)
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

#endif //__UTASK_COMPAT_H__