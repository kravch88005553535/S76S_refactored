#include <stm32l073xx.h>

#include "uart.h"
#include "adc_constants.h"
#include "graphics_constants.h"


void clearterminal(void)
{
    DMA1_Channel4->CCR &= ~DMA_CCR_EN;
    uart_buf[0][0]= '\f';
    DMA1_Channel4->CNDTR = 1;
    DMA1_Channel4->CCR |= DMA_CCR_EN;

    while ((USART2->ISR & USART_ISR_TC) == USART_ISR_TC) {}
    uart_buf[0][0]= GRAPHICS_VOLTAGE_MAX / 1000 + 48;
}

void printaxes(uint8_t a_x_axis_offset, uint8_t a_y_axis_offset)
{
    for (int y = Y_AXIS_OFFSET; y<UARTBUF_Y_ARRAY_SIZE; y++)
    {
        uart_buf[UARTBUF_X_ARRAY_SIZE-a_x_axis_offset-1][y] = '-';
    }

    for (int x = 0; x<BAR_GRAPH_HEIGHT; x++)
    {
        uart_buf[x][a_y_axis_offset] = '|';
    }

    for (int x = 0; x<UARTBUF_X_ARRAY_SIZE; x++)
    {
        uart_buf[x][UARTBUF_Y_ARRAY_SIZE-1] = '\n';
        uart_buf[x][UARTBUF_Y_ARRAY_SIZE-2] = '\r';
        
        if ((x <= BAR_GRAPH_HEIGHT) && (x % (BAR_GRAPH_HEIGHT/5) == 0))
        {
         uint16_t voltage = GRAPHICS_VOLTAGE_MIN + (GRAPHICS_VOLTAGE_MAX - GRAPHICS_VOLTAGE_MIN) / BAR_GRAPH_HEIGHT * x;
         uart_buf[BAR_GRAPH_HEIGHT - x ][0] = voltage / 1000 + 48;
         uart_buf[BAR_GRAPH_HEIGHT - x ][1] = '.';
         uart_buf[BAR_GRAPH_HEIGHT - x ][2] = voltage % 1000 / 100 + 48;
         uart_buf[BAR_GRAPH_HEIGHT - x ][3] = voltage % 100 / 10 + 48;
        }
    }
}

void printbargraph (int32_t a_adc_voltage, uint8_t a_iteration)
{

    for(int i = 1; i<= BAR_GRAPH_HEIGHT; i++)
    {
        (((a_adc_voltage-GRAPHICS_VOLTAGE_MIN) * BAR_GRAPH_HEIGHT / (GRAPHICS_VOLTAGE_MAX - GRAPHICS_VOLTAGE_MIN)) < i) ?
        (uart_buf[BAR_GRAPH_HEIGHT-i][a_iteration+Y_AXIS_OFFSET] = ' '):
        (uart_buf[BAR_GRAPH_HEIGHT-i][a_iteration+Y_AXIS_OFFSET] = 254);
    }
    

    
//    for(int i = 1; i<= BAR_GRAPH_HEIGHT; i++)
//    {
//        ((a_adc_voltage * BAR_GRAPH_HEIGHT / ADC_VOLTAGE_MAX) < i) ?
//        (uart_buf[BAR_GRAPH_HEIGHT-i][a_iteration+Y_AXIS_OFFSET] = ' ') :
//        (uart_buf[BAR_GRAPH_HEIGHT-i][a_iteration+Y_AXIS_OFFSET] = 254);
//    }
}

void printgraphics(void)
{
    senduartbufer();
}
