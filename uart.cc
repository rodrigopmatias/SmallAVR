#include "uart.h"

void uartPutCharStream(char c, FILE * stream);
char uartGetCharStream(FILE * stream);

void uartInit(void) {
    UBRRxH = UBRRH_VALUE;
    UBRRxL = UBRRL_VALUE;

    fdev_setup_stream(&uartInput, 0, uartGetCharStream, _FDEV_SETUP_READ);
    fdev_setup_stream(&uartOutput, uartPutCharStream, 0, _FDEV_SETUP_WRITE);

    #if USE_2X
    UCSRxA |= _BV(U2Xx);
    #else
    UCSRxA &= ~(_BV(U2Xx));
    #endif

    UCSRxC = _BV(UCSZx1) | _BV(UCSZx0); /* 8-bit data */
    UCSRxB = _BV(RXENx) | _BV(TXENx);   /* Enable RX and TX */
}

void uartPutChar(char c) {
    while(!UCSRxA & (1 << TXCx));  //Wait until transmission ready.
    UDRx = c;
}

char uartGetChar(void) {
    while(!UCSRxA & (1 << RXCx));  //Wait until transmission ready.
    return UDRx;
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
