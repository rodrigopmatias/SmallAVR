#ifndef __UART_H__
#define __UART_H__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <inttypes.h>

#include <SmallAVR/data/fifo.h>

#if defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48PA__) || \
        defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88PA__) || \
        defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) || \
        defined(__AVR_ATmega328P__)
#include <SmallAVR/uart/uart-328p.h>
#elif defined(__AVR_ATmega8__)
#include <SmallAVR/uart/uart-8.h>
#else
#error uC not supported!
#endif

#ifndef BAUD
#define BAUD        9600
#endif //BAUD

#include <util/setbaud.h>

#ifndef UART_RX_BUFFER_SIZE
#define UART_RX_BUFFER_SIZE     32
#endif

/**
 * This function start enviroment for UART communication
 **/
void uartInit(void);

/**
 * This function check if rx buffer is empty
 **/
uint8_t uartBufferIsEmpty(void);

/**
 * This function send byte for UART.
 * @param c byte to send
 **/
void uartPutChar(uint8_t c);

/**
 * This function read byte from UART.
 * @return Return one byte from UART.
 **/
uint8_t uartGetChar(void);

/**
 * This function make the UART as default IO of system.
 **/
void uartAsStdio(void);

static FILE uartOutput;
static FILE uartInput;

#endif //__UART_H__
