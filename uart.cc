#include "uart.h"

void uartPutCharStream(uint8_t c, FILE * stream);
uint8_t uartGetCharStream(FILE * stream);

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

    UCSRxC |= _BV(URSELx) | _BV(UCSZx1) | _BV(UCSZx0); /* 8-bit data */
    UCSRxB |= _BV(RXENx) | _BV(TXENx) | _BV(RXCIEx) | _BV(TXCIEx);

    __fifo.nav_rx = 0;
    __fifo.nav_tx = 0;
    __fifo.pos_rx = 0;
    __fifo.pos_tx = 0;
}

void uartPutChar(uint8_t c) {
    while(!UCSRxA & (1 << TXCx));  //Wait until transmission ready.
    UDRx = c;
}

uint8_t uartGetChar(void) {
    while(!UCSRxA & (1 << RXCx));  //Wait until transmission ready.
    return UDRx;
}

uint8_t uartGetCharStream(FILE * stream) {
    return uartGetChar();
}

void uartPutCharStream(uint8_t c, FILE * stream) {
    uartPutChar(c);
}

void uartAsStdio(void) {
    stdout = &uartOutput;
    stdin = &uartInput;
}
