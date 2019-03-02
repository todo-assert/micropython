#include <stdio.h>
#include <string.h>

#include "py/runtime.h"
#include "py/mphal.h"
#include "extmod/machine_spi.h"
#include "irq.h"
#include "pin.h"
#include "genhdr/pins.h"
#include "bufhelper.h"
#include "spi.h"
#include "storage.h"
#include "genhdr/pins.h"

extern const spi_t spi_obj[6];

extern void spi_deinit(const spi_t *spi_obj);
extern void spi_transfer(const spi_t *self, size_t len, const uint8_t *src, uint8_t *dest, uint32_t timeout);
int mp_periph_spi_ioctl(void *self_in, uint32_t cmd) {
    spi_t *self = (spi_t *)self_in;
    SPI_InitTypeDef *init = &self->spi->Init;
    switch (cmd) {
        case MP_SPI_IOCTL_INIT:
            spi_init0();
            spi_deinit(self);
            // these parameters are not currently configurable
            init->BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
            init->CLKPhase = SPI_PHASE_1EDGE;
            init->CLKPolarity = SPI_POLARITY_LOW;
            init->CRCCalculation = SPI_CRCCALCULATION_DISABLED;
            init->CRCPolynomial = 7;
            init->DataSize = SPI_DATASIZE_8BIT;
            init->Direction = SPI_DIRECTION_2LINES;
            init->FirstBit = SPI_FIRSTBIT_MSB;
            init->Mode = SPI_MODE_MASTER;

            init->NSS = SPI_NSS_SOFT;
            init->TIMode = SPI_TIMODE_DISABLE;

            spi_init(self, false);
            break;

        case MP_SPI_IOCTL_DEINIT:
            spi_deinit(self);
            break;
    }

    return 0;
}

void mp_periph_spi_transfer(void *self_in, size_t len, const uint8_t *src, uint8_t *dest) {
    spi_t *self = (spi_t *)self_in;
    spi_transfer(self, len, src, dest, len+100);
}

const mp_spi_proto_t mp_periph_spi_proto = {
    .ioctl = mp_periph_spi_ioctl,
    .transfer = mp_periph_spi_transfer,
};
// External SPI flash uses standard SPI interface
/*
*/
const mp_soft_spi_obj_t soft_spi_bus = {
    .delay_half = MICROPY_HW_SOFTSPI_MIN_DELAY,
    .polarity = 0,
    .phase = 0,
    .sck = MICROPY_HW_SPIFLASH_SCK,
    .mosi = MICROPY_HW_SPIFLASH_MOSI,
    .miso = MICROPY_HW_SPIFLASH_MISO,
};

const mp_spiflash_config_t spiflash_config = {
    .bus_kind = MP_SPIFLASH_BUS_SPI,
    .bus.u_spi.cs = MICROPY_HW_SPIFLASH_CS,
    .bus.u_spi.data = (void*)&soft_spi_bus,
    // .bus.u_spi.data = (void*)MICROPY_HW_SPIFLASH_INDEX,
    .bus.u_spi.proto = &mp_soft_spi_proto,
    // .bus.u_spi.proto = &mp_periph_spi_proto,
};

spi_bdev_t spi_bdev;
