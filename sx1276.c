#include <stm32l073xx.h>
#include "sx1276.h"
#include "systick.h"
#include "spi.h"
#include "sx1276Regs-Fsk.h"
#include "sx1276Regs-LoRa.h"
#include "sx1276_constants.h"

void sx1276_enableantenna(uint8_t is_enabled)
{
    static const uint8_t antenna_pin = 0x01;
    if (!is_enabled) GPIOA->ODR |= antenna_pin; //toggle antenna_pin to 1 
    else GPIOA->ODR &= ~antenna_pin;//toggle antenna_pin 1 
}
void sx1276_setchannelfrequency (uint32_t a_channel_frequency)
{
    a_channel_frequency = (uint32_t)((double)a_channel_frequency/(double)FREQ_STEP);
    
    sx1276_writebyte(REG_FRFMSB, (uint8_t)((a_channel_frequency >> 16) & 0xFF));
    sx1276_writebyte(REG_FRFMID, (uint8_t)((a_channel_frequency >> 8) & 0xFF));
    sx1276_writebyte(REG_FRFLSB, (uint8_t)(a_channel_frequency & 0xFF));
}
void sx1276_setoperationmode(uint8_t a_operationmode)
{
    if(a_operationmode == RF_OPMODE_SLEEP)
        sx1276_enableantenna(0);
    else if(a_operationmode == RF_OPMODE_TRANSMITTER)
        sx1276_enableantenna(1);
    else
        sx1276_enableantenna(0);

    sx1276_writebyte(REG_OPMODE,(sx1276_readbyte(REG_OPMODE) & RF_OPMODE_MASK) | a_operationmode);
    uint8_t temp = sx1276_readbyte(REG_OPMODE);
    while ((sx1276_readbyte(REG_OPMODE)&~RF_OPMODE_MASK) != a_operationmode) {__ASM("nop");}
}

void sx1276_setmodemtype(Modem_types a_modem_type)
{
    switch (a_modem_type)
    {
        case Modem_types_FSK:
        sx1276_setoperationmode(RF_OPMODE_SLEEP);
        sx1276_writebyte(REG_OPMODE,(sx1276_readbyte(REG_OPMODE) & RFLR_OPMODE_LONGRANGEMODE_MASK) | RFLR_OPMODE_LONGRANGEMODE_OFF);
        break;
        case Modem_types_LoRa:
        break;
    }
}

void sx1276_reset(void)
{
    GPIOB->ODR &= ~GPIO_ODR_OD10;
    systick_delay_ms(3);
    GPIOB->ODR |= GPIO_ODR_OD10;
    systick_delay_ms(7);
}


void sx1276_calibrate_rx(void)
{
    uint8_t pa_register_temp = sx1276_readbyte(REG_PACONFIG);
    
    uint32_t initial_frequency = (double)(((uint32_t) sx1276_readbyte(REG_FRFMSB) << 16) |
                              ((uint32_t)sx1276_readbyte(REG_FRFMID) << 8) |
                              ((uint32_t)sx1276_readbyte(REG_FRFLSB)) ) *(double)FREQ_STEP;
    
    sx1276_writebyte (REG_PACONFIG , 0x00);
    
    //Rx chain calibration for LF band
    sx1276_writebyte(REG_IMAGECAL,(sx1276_readbyte(REG_IMAGECAL) & RF_IMAGECAL_IMAGECAL_MASK) | RF_IMAGECAL_IMAGECAL_START);
    while((sx1276_readbyte(REG_IMAGECAL) & RF_IMAGECAL_IMAGECAL_RUNNING) == RF_IMAGECAL_IMAGECAL_RUNNING) __ASM("nop");
    
    sx1276_setchannelfrequency(868000000/*Hz*/);
    
    //Rx chain calibration for HF band
    sx1276_writebyte(REG_IMAGECAL,(sx1276_readbyte(REG_IMAGECAL) & RF_IMAGECAL_IMAGECAL_MASK) | RF_IMAGECAL_IMAGECAL_START);
    while((sx1276_readbyte(REG_IMAGECAL) & RF_IMAGECAL_IMAGECAL_RUNNING) == RF_IMAGECAL_IMAGECAL_RUNNING) __ASM("nop");

    //Restore context
    sx1276_writebyte(REG_PACONFIG, pa_register_temp);
    sx1276_setchannelfrequency(initial_frequency);
}

void sx1276_configuretx(uint32_t a_bitrate)
{
    uint8_t temp;
    
    sx1276_setoperationmode(RF_OPMODE_STANDBY);
    sx1276_setmodemtype(Modem_types_FSK);
    
    temp = sx1276_readbyte(REG_OPMODE);
    
    //set power to 2 dBm
    sx1276_writebyte(REG_PACONFIG,  0xF0);
    
    sx1276_writebyte( REG_FDEVMSB, ( uint8_t )( 0 >> 8 ) );
    sx1276_writebyte( REG_FDEVLSB, ( uint8_t )( 0 & 0xFF ) );
    
    //bitrate setup
    a_bitrate = (uint16_t)((double)XTAL_FREQ/(double)a_bitrate); 
    sx1276_writebyte(REG_BITRATEMSB, (uint8_t)(a_bitrate >> 8));
    sx1276_writebyte(REG_BITRATELSB, (uint8_t)(a_bitrate & 0xFF));
    
    //preamble len = 5 
    sx1276_writebyte( REG_PREAMBLEMSB, ( 5 >> 8 ) & 0x00FF );
    sx1276_writebyte( REG_PREAMBLELSB, 5 & 0xFF );
    
    //fixlen =0 crcon =0
    sx1276_writebyte( REG_PACKETCONFIG1,
                         ( sx1276_readbyte( REG_PACKETCONFIG1 ) &
                           RF_PACKETCONFIG1_CRC_MASK &
                           RF_PACKETCONFIG1_PACKETFORMAT_MASK ) |
                           RF_PACKETCONFIG1_PACKETFORMAT_VARIABLE  |
                           ( 0 << 4 ));
//    sx1276_writebyte(REG_PACKETCONFIG2, sx1276_readbyte(REG_PACKETCONFIG2)&RF_PACKETCONFIG2_DATAMODE_MASK |RF_PACKETCONFIG2_DATAMODE_CONTINUOUS);

    temp = sx1276_readbyte(REG_PACKETCONFIG2);
    sx1276_setoperationmode(RF_OPMODE_TRANSMITTER);
}

void sx1276_readbuffer(uint8_t a_address, uint8_t* ap_buffer, uint8_t a_size)
{
    GPIOB-> ODR &= ~GPIO_ODR_OD12;  //NSS=0
    
    static const uint8_t wnr_bit = 0x80;

    spi_transmit((SPI_TypeDef*)SPI2_BASE, a_address & ~wnr_bit);
    
    for(int i = 0; i < a_size; i++ )
    {
        ap_buffer[i] = spi_recieve((SPI_TypeDef*)SPI2_BASE);
    }
    
    GPIOB-> ODR |= GPIO_ODR_OD12;  //NSS=1
}

void sx1276_writebuffer(uint8_t a_address, uint8_t* ap_buffer, uint8_t a_size)
{
    GPIOB-> ODR &= ~GPIO_ODR_OD12;  //NSS=0
    
    static const uint8_t wnr_bit = 0x80;
    
    spi_transmit((SPI_TypeDef*)SPI2_BASE, a_address | wnr_bit);
    
    for(int i = 0; i < a_size; i++ )
    {
        spi_transmit((SPI_TypeDef*)SPI2_BASE,ap_buffer[i]);
    }
    
    GPIOB-> ODR |= GPIO_ODR_OD12;  //NSS=1
}


uint8_t sx1276_readbyte (uint8_t a_address)
{
    uint8_t read_data = 0;
    sx1276_readbuffer(a_address, &read_data , 1);
    return read_data;
}

void sx1276_writebyte(uint8_t a_address, uint8_t a_data)
{
    sx1276_writebuffer(a_address, &a_data, 1);
}

void sx1276_init(void)
{
    sx1276_reset();
//    sx1276_calibrate_rx();
    sx1276_setoperationmode(RF_OPMODE_SLEEP);
    sx1276_setmodemtype(Modem_types_FSK);
    sx1276_setchannelfrequency(863000000/*Hz*/);
    sx1276_configuretx(4800);
}
