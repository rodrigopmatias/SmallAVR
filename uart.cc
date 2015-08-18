#include "uart.h"

void uartPutCharStream(uint8_t c, FILE * stream);
uint8_t uartGetCharStream(FILE * stream);

volatile uint8_t __rx_buffer_memory[UART_RX_BUFFER_SIZE];

volatile fifo_buffer_t __rx_buffer;

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

    UCSRxB = _BV(RXENx) | _BV(TXENx) | _BV(RXCIEx);
    #ifdef URSELx
    UCSRxC = _BV(URSELx) | _BV(UCSZx1) | _BV(UCSZx0); /* 8-bit data */
    #else
    UCSRxC = _BV(UCSZx1) | _BV(UCSZx0); /* 8-bit data */
    #endif

    fifoInit(&__rx_buffer, __rx_buffer_memory, UART_RX_BUFFER_SIZE);
}

uint8_t uartBufferIsEmpty(void) {
    return fifoIsEmpty(&__rx_buffer);
}

void uartPutChar(uint8_t c) {
    loop_until_bit_is_set(UCSRxA, UDREx);
    UDRx = c;
}

uint8_t uartGetChar(void) {
    if(!fifoIsEmpty(&__rx_buffer))
        return fifoPop(&__rx_buffer);
    else
        return 0x0;
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

ISR(__UART_RX_READY_INTERRUPT) {
    if(!fifoIsFull(&__rx_buffer))
        fifoPush(&__rx_buffer, (const uint8_t)UDRx);
}
