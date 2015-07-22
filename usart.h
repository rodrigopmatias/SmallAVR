#ifndef __USART_H__
#define __USART_H__

#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>

#include <SmallAVR/data/fifo.h>

#if defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48PA__) || \
        defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88PA__) || \
        defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) || \
        defined(__AVR_ATmega328P__)
#include <SmallAVR/usart/usart-328p.h>
#elif defined(__AVR_ATmega8__)
#include <SmallAVR/usart/usart-8.h>
#else
#error uC not supported!
#endif

#ifndef BAUD
#define BAUD        9600
#endif //BAUD

#include <util/setbaud.h>

#ifndef USART_TX_BUFFER_SIZE
#define USART_TX_BUFFER_SIZE     4
#endif

#ifndef USART_RX_BUFFER_SIZE
#define USART_RX_BUFFER_SIZE     32
#endif

/**
 * This function start enviroment for USART communication
 **/
void usartInit(void);

/**
 * This function send byte for USART.
 * @param c byte to send
 **/
void usartPutChar(uint8_t c);

/**
 * This function read byte from USART.
 * @return Return one byte from USART.
 **/
uint8_t usartGetChar(void);

/**
 * This function make the USART as default IO of system.
 **/
void usartAsStdio(void);

static FILE usartOutput;
static FILE usartInput;

#endif //__USART_H__
