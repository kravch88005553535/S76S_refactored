#include <stm32l073xx.h>
#include "stm32l0xx_hal.h"
#include "stm32l0xx_ll_adc.h"

#include "graphics.h"
#include "uart.h"
#include "adc.h"
#include "sx1276.h"
#include "sx1276Regs-Fsk.h"
#include "sx1276_constants.h"

void TIM2_IRQHandler(void)
{
//    TIM2->CR1 &= ~TIM_CR1_CEN;
    static uint16_t iteration = 1; // 1 is init value
    
    if(iteration > BAR_GRAPH_NUM*2)
    {
        sx1276_setoperationmode(RF_OPMODE_STANDBY);
        sx1276_setchannelfrequency(LOWEST_FREQUENCY);
        sx1276_setoperationmode(RF_OPMODE_TRANSMITTER);
        clearterminal();
        printgraphics();
        iteration = 1; 

    } else
    {
        if(iteration%2 == 1)
        {
            start_adc();
        }
        else
        {
            printbargraph(getadcvoltage(), iteration / 2); 

            const uint32_t fraction = (HIGHEST_FREQUENCY - LOWEST_FREQUENCY) / BAR_GRAPH_NUM;
            uint32_t futurefreq = LOWEST_FREQUENCY + fraction * (iteration / 2 - 1);
            sx1276_setoperationmode(RF_OPMODE_STANDBY);
            sx1276_setchannelfrequency(futurefreq);
            sx1276_setoperationmode(RF_OPMODE_TRANSMITTER);
        }
        
        iteration++;
    }

//    TIM2->CR1 |= TIM_CR1_CEN;
    TIM2->SR &= ~TIM_SR_UIF;
}

void SetupInterrupts(void)
{
//    NVIC_SetPriority(DMA1_Channel4_5_6_7_IRQn,0); 
    NVIC_SetPriority(TIM2_IRQn,1);
}

void EnableInterrupts(void)
{
//    NVIC_EnableIRQ(DMA1_Channel4_5_6_7_IRQn);
    NVIC_EnableIRQ(TIM2_IRQn);
}

//void DMA1_Channel4_5_6_7_IRQHandler (void)
//{
//    DMA1->IFCR |= DMA_IFCR_CGIF4;
//    DMA1->IFCR |= DMA_IFCR_CHTIF4;
//    DMA1->IFCR |= DMA_IFCR_CTCIF4;
//    DMA1->IFCR |= DMA_IFCR_CTEIF4;
//    __ASM ("nop");
//}

