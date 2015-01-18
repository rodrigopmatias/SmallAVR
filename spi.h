#ifndef __SPI_H__
#define __SPI_H__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include "spi_compat.h"

#define SPI_ACK 0x7F

static uint8_t (* spi_event)(const uint8_t data);

#define MODE_SLAVE           0
#define MODE_MASTER          1

#define POLARITY_RISING      0
#define POLARITY_FALLING     1

#define PHASE_SAMPLE         0
#define PHASE_SETUP          1

void spiSend(const uint8_t data);

void spiInit(const uint8_t mode, const uint8_t polarity, const uint8_t phase,
        const uint8_t clock_set, const uint8_t (* event)(const uint8_t data)) __attribute__((always_inline));

#endif /* __SPI_H__ */