#include <stm32l073xx.h>

void spi_init(void)
{
    SPI2->CR1 |= SPI_CR1_BR_0; 
    SPI2->CR1 &= ~SPI_CR1_CPOL; //cpol=0
    SPI2->CR1 &= ~SPI_CR1_CPHA; //cpha=0
    SPI2->CR1 &= ~SPI_CR1_BIDIMODE;
    SPI2->CR1 &= ~SPI_CR1_LSBFIRST;
    SPI2->CR1 &= ~SPI_CR1_CRCEN; 
    SPI2->CR1 &= ~SPI_CR1_CRCNEXT;
    SPI2->CR1 |= SPI_CR1_SSM;  //software slave management
    SPI2->CR1 |= SPI_CR1_SSI;
    SPI2->CR1 &= ~SPI_CR1_DFF;
    SPI2->CR1 |= SPI_CR1_MSTR;
    
    SPI2->CR1 |= SPI_CR1_SPE; //spi enable
}

void spi_transmit(SPI_TypeDef* a_spi_interface, uint8_t a_data)
{
    uint8_t rxdata = 0;
    while ((a_spi_interface->SR & SPI_SR_TXE) != SPI_SR_TXE) __ASM("nop");
    a_spi_interface->DR = a_data & 0xFF;
    while ((a_spi_interface->SR & SPI_SR_RXNE) != SPI_SR_RXNE) __ASM("nop");
    rxdata = a_spi_interface->DR;
}

uint8_t spi_recieve (SPI_TypeDef* a_spi_interface)
{
    uint8_t rxdata = 0;
    while ((a_spi_interface->SR & SPI_SR_TXE) != SPI_SR_TXE) __ASM("nop");
    a_spi_interface->DR = 0 & 0xFF;
    while ((a_spi_interface->SR & SPI_SR_RXNE) != SPI_SR_RXNE) __ASM("nop");
    rxdata = a_spi_interface->DR;
    return rxdata;
}
