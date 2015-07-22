#include "usart.h"

void usartPutCharStream(uint8_t c, FILE * stream);
uint8_t usartGetCharStream(FILE * stream);

static uint8_t __rx_buffer_memory[USART_RX_BUFFER_SIZE];
static uint8_t __tx_buffer_memory[USART_TX_BUFFER_SIZE];

static fifo_buffer_t __rx_buffer;
static fifo_buffer_t __tx_buffer;

void usartInit(void) {
    cli();
    UBRRxH = UBRRH_VALUE;
    UBRRxL = UBRRL_VALUE;

    fdev_setup_stream(&usartInput, 0, usartGetCharStream, _FDEV_SETUP_READ);
    fdev_setup_stream(&usartOutput, usartPutCharStream, 0, _FDEV_SETUP_WRITE);

    #if USE_2X
    UCSRxA |= _BV(U2Xx);
    #else
    UCSRxA &= ~(_BV(U2Xx));
    #endif

    UCSRxB = _BV(RXENx) | _BV(TXENx) | _BV(RXCIEx) | _BV(TXCIEx);
    #ifdef URSELx
    UCSRxC = _BV(URSELx) | _BV(UCSZx1) | _BV(UCSZx0); /* 8-bit data */
    #else
    UCSRxC = _BV(UCSZx1) | _BV(UCSZx0); /* 8-bit data */
    #endif
    sei();

    fifo_init(&__rx_buffer, __rx_buffer_memory, USART_RX_BUFFER_SIZE);
    fifo_init(&__tx_buffer, __tx_buffer_memory, USART_TX_BUFFER_SIZE);
}

void usartPutChar(uint8_t c) {
    if(!fifo_is_full(&__tx_buffer)) fifo_push(&__tx_buffer, (const uint8_t)c);
}

uint8_t usartGetChar(void) {
    if(!fifo_is_empty(&__rx_buffer))
        return fifo_pop(&__rx_buffer);
    else
        return 0x0;
}

uint8_t usartGetCharStream(FILE * stream) {
    return usartGetChar();
}

void usartPutCharStream(uint8_t c, FILE * stream) {
    usartPutChar(c);
}

void usartAsStdio(void) {
    stdout = &usartOutput;
    stdin = &usartInput;
}

ISR(__USART_TX_READY_INTERRUPT) {
    cli();
    if(!fifo_is_empty(&__tx_buffer)) UDRx = fifo_pop(&__tx_buffer);
    sei();
}

ISR(__USART_RX_READY_INTERRUPT) {
    cli();
    if(!fifo_is_full(&__rx_buffer)) fifo_push(&__rx_buffer, (const uint8_t)UDRx);
    sei();
}
