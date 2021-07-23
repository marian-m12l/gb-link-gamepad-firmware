
#ifndef _PIO_SECONDARY_H
#define _PIO_SECONDARY_H

#include "hardware/pio.h"
#include "secondary.pio.h"

typedef struct pio_secondary_inst {
    PIO pio;
    uint sm;
    uint cs_pin;
} pio_secondary_inst_t;

void pio_secondary_read8_blocking(const pio_secondary_inst_t *secondary, uint8_t *dst, size_t len);
void pio_secondary_read8(const pio_secondary_inst_t *secondary, uint8_t *dst, size_t len);
bool pio_secondary_available(const pio_secondary_inst_t *secondary);
void pio_secondary_write8_blocking(const pio_secondary_inst_t *secondary, const uint8_t *src, size_t len);

#endif
