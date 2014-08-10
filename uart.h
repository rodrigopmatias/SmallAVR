#ifndef __UART_H__
#define __UART_H__

#ifndef BAUD
#define BAUD        9600
#endif //BAUD

#include <avr/io.h>
#include <util/setbaud.h>
#include <stdio.h>

/**
 * This function start enviroment for UART communication
 **/
void uartInit(void);

/**
 * This function send byte for UART.
 * @param c byte to send
 **/
void uartPutChar(char c);

/**
 * This function read byte from UART.
 * @return Return one byte from UART.
 **/
char uartGetChar(void);

/**
 * This function make the UART as default IO of system.
 **/
void uartAsStdio(void);

static FILE uartOutput;
static FILE uartInput;

#endif //__UART_H__