#include "uart.h"

void uartPutCharStream(char c, FILE * stream);
char uartGetCharStream(FILE * stream);

void uartInit(void) {
    UBRRH = UBRRH_VALUE;
    UBRRL = UBRRL_VALUE;

    fdev_setup_stream(&uartInput, 0, uartGetCharStream, _FDEV_SETUP_READ);
    fdev_setup_stream(&uartOutput, uartPutCharStream, 0, _FDEV_SETUP_WRITE);

    #if USE_2X
    UCSRA |= _BV(U2X);
    #else
    UCSRA &= ~(_BV(U2X));
    #endif

    UCSRC = _BV(UCSZ1) | _BV(UCSZ0); /* 8-bit data */
    UCSRB = _BV(RXEN) | _BV(TXEN);   /* Enable RX and TX */
}

void uartPutChar(char c) {
    if(c == '\n') uartPutChar('\r');
    loop_until_bit_is_set(UCSRA, TXC); /* Wait until transmission ready. */
    UDR = c;
}

char uartGetChar(void) {
    loop_until_bit_is_set(UCSRA, RXC); /* Wait until data exists. */
    return UDR;
}

char uartGetCharStream(FILE * stream) {
    return uartGetChar();
}

void uartPutCharStream(char c, FILE * stream) {
    uartPutChar(c);
}

void uartAsStdio(void) {
    stdout = &uartOutput;
    stdin = &uartInput;
}
