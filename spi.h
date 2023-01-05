#ifndef __SPI_H__
#define __SPI_H__
#include <stm32l073xx.h>
#include <stdint.h>

void spi_init(void);
void spi_transmit(SPI_TypeDef* a_spi_interface, uint8_t a_data);
uint8_t spi_recieve (SPI_TypeDef* a_spi_interface);

#endif //__SPI_H__