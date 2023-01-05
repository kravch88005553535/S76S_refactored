#include <stm32l073xx.h>

#include "stm32l0xx_ll_usart.h"
#include "uart_constants.h"

#include "graphics.h"

uint8_t uart_buf[UARTBUF_X_ARRAY_SIZE][UARTBUF_Y_ARRAY_SIZE] = {};

void uart_init()
{
    LL_USART_InitTypeDef usart_initstruct;
    usart_initstruct.BaudRate = 921600U;
    usart_initstruct.DataWidth = LL_USART_DATAWIDTH_8B;
    usart_initstruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    usart_initstruct.OverSampling = LL_USART_OVERSAMPLING_16;
    usart_initstruct.Parity = LL_USART_PARITY_NONE;
    usart_initstruct.StopBits = LL_USART_STOPBITS_1;
    usart_initstruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  
    LL_USART_ClockInitTypeDef usart_clockinitstruct;
    LL_USART_ClockStructInit(&usart_clockinitstruct);
    LL_USART_ClockInit(USART2, &usart_clockinitstruct);
    LL_USART_Init(USART2, &usart_initstruct);
    USART2->CR3 |= USART_CR3_DMAT;
    LL_USART_Enable(USART2);

    for (int y=0; y<UARTBUF_Y_ARRAY_SIZE; y++)
        for (int x=0; x<UARTBUF_X_ARRAY_SIZE; x++)
        {
        uart_buf[x][y] =' ';
        }
    printaxes(X_AXIS_OFFSET,Y_AXIS_OFFSET);
}

void senduartbufer()
{
    DMA1_Channel4->CCR &= ~DMA_CCR_EN;
    DMA1_Channel4->CNDTR = UARTBUF_X_ARRAY_SIZE*UARTBUF_Y_ARRAY_SIZE;
    DMA1_Channel4->CCR |= DMA_CCR_EN;
    
    TIM2->CR1 &= ~TIM_CR1_CEN;
    while ((USART2->ISR & USART_ISR_TC) == USART_ISR_TC) {};
    TIM2->CR1 |= TIM_CR1_CEN;
}