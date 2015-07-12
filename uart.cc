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

    UCSRxB |= _BV(RXENx) | _BV(TXENx) | _BV(RXCIEx) | _BV(TXCIEx);
    #ifdef URSELx
    UCSRxC |= _BV(URSELx) | _BV(UCSZx1) | _BV(UCSZx0); /* 8-bit data */
    #else
    UCSRxC |= _BV(UCSZx1) | _BV(UCSZx0); /* 8-bit data */
    #endif

    fifo_init(&__rx_buffer, __rx_buffer_memory, USART_RX_BUFFER_SIZE);
    fifo_init(&__tx_buffer, __tx_buffer_memory, USART_TX_BUFFER_SIZE);
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
