#include "spi.h"

ISR(SPI_STC_vect) {
    uint8_t data;

    if(spi_event) {
        data = SPDR;
        SPDR = spi_event(data);
    }
}

void spiInit(const uint8_t mode, const uint8_t polarity, const uint8_t phase,
        const uint8_t clock_set, const uint8_t (* event)(const uint8_t data)) {
    cli();
    SPCR = 0;
    SPCR |= (1 << SPIE) | (1 << SPE) | (1 << DORD);

    if(mode == MODE_MASTER)
        SPCR |= (1 << MSTR);
    if(polarity == POLARITY_FALLING)
        SPCR |= (1 << CPOL);
    if(phase == PHASE_SETUP)
        SPCR |= (1 << CPHA);

    SPCR |= clock_set;
    spi_event = event;
    sei();
}

void spiSend(const uint8_t data) {
    cli();
    SPDR = data;
    sei();
}