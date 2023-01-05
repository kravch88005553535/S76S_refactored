#include <stm32l073xx.h>
#include "uart.h"

void dma_init(void)
{
//  dma_channel 4 

    DMA1_CSELR->CSELR |= 0b0100 << DMA_CSELR_C4S_Pos;
    DMA1_Channel4->CPAR = (uint32_t)(&(USART2->TDR)); 
    DMA1_Channel4->CMAR = (uint32_t)(&uart_buf[0][0]);
    DMA1_Channel4->CNDTR = 8;
//    DMA1_Channel4->CCR |= DMA_CCR_PL;       //DMA_PRIORITY_VERY_HIGH   
    DMA1_Channel4->CCR &= ~DMA_CCR_MSIZE;     //memory size 8bit  
    DMA1_Channel4->CCR &= ~DMA_CCR_PSIZE;     //peripherals size 8bit 
    DMA1_Channel4->CCR |= DMA_CCR_MINC;       //memory increment enabled
    DMA1_Channel4->CCR &= ~DMA_CCR_PINC;      //peripherals incerement disabled
    DMA1_Channel4->CCR &= ~DMA_CCR_CIRC;      //circular mode disable
    DMA1_Channel4->CCR |= DMA_CCR_DIR;        //read from memory
//    DMA1_Channel4->CCR |= DMA_CCR_TEIE;       //transfer error interrupt enable
//    DMA1_Channel4->CCR |= DMA_CCR_HTIE;       //half transfer interrupt enable
//    DMA1_Channel4->CCR |= DMA_CCR_TCIE;       //transfer complete interrupt enable
    DMA1_Channel4->CCR |= DMA_CCR_EN;         //channel enable
}