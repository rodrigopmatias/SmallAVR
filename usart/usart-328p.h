#ifndef __USART_328P__
#define __USART_328P__

#include <avr/io.h>
#include <avr/interrupt.h>

#define UBRRxH   UBRR0H
#define UBRRxL   UBRR0L
#define U2Xx     U2X0
#define UCSRxA   UCSR0A
#define UCSRxB   UCSR0B
#define UCSRxC   UCSR0C
#define UCSZx0   UCSZ00
#define UCSZx1   UCSZ01
#define RXENx    RXEN0
#define TXENx    TXEN0
#define RXCx     RXC0
#define RXCIEx   RXCIE0
#define TXCx     TXC0
#define TXCIEx   TXCIE0
#define UDRx     UDR0
#define UDREx    UDRE0
// #define URSELx   URSEL0

#define __USART_TX_READY_INTERRUPT       USART_TX_vect
// #define __USART_TX_READY_INTERRUPT       USART_UDRE_vect
#define __USART_RX_READY_INTERRUPT       USART_RX_vect

#endif /* __USART_328P__ */
