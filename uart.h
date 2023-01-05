#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>
#include "uart_constants.h"

extern uint8_t uart_buf[UARTBUF_X_ARRAY_SIZE][UARTBUF_Y_ARRAY_SIZE];

void uart_init(void);
void senduartbufer(void);

#endif //__UART_H__