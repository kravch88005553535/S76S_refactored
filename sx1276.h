#ifndef __SX1276_H__
#define __SX1276_H__
#include <stdint.h>

typedef enum : int
{
    Modem_types_FSK = 0,
    Modem_types_LoRa
} Modem_types;

void sx1276_enableantenna(uint8_t is_enabled);
void sx1276_setchannelfrequency (uint32_t a_channel_frequency);
void sx1276_setoperationmode(uint8_t a_operationmode);
void sx1276_setmodemtype(Modem_types a_modem_type);
void sx1276_reset(void);
//void sx1276_calibrate_rx(void);
void sx1276_configuretx(uint32_t);
void sx1276_configurerx(void);
void sx1276_readbuffer(uint8_t a_address, uint8_t* ap_buffer, uint8_t a_size);
void sx1276_writebuffer(uint8_t a_address, uint8_t* ap_buffer, uint8_t a_size);
uint8_t sx1276_readbyte (uint8_t a_address);
void sx1276_writebyte(uint8_t a_address, uint8_t a_data);
void sx1276_init(void);


#endif //__SX1276_H__