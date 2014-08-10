#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdint.h>
#include <avr/sleep.h>
#include "uart.h"
#include "utask.h"

#if defined(__AVR_ATmega640__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define LED             DDB7
#elif defined(__AVR_ATmega48P__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328P__)
#define LED             DDB5
#elif defined(__AVR_ATmega8__)
#define LED             DDB1
#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
#define LED             DDB3
#endif

#define forever()               while(1)

void ledStatus(void);

#endif /* __MAIN_H__ */