#include <stm32l073xx.h>
#include "timer_constants.h"
#include "rcc_constants.h"
#include "graphics_constants.h"

void timer_init(void)
{
    TIMER->CNT = 0;
    TIMER->ARR = TIM_ARR_MAX / BAR_GRAPH_NUM / 2;
    TIMER->PSC = PLL_OUT_CLOCK / TIM_ARR_MAX * 0.4 /*sec*/;
    TIMER->DIER |= TIM_DIER_UIE;
    TIMER->CR1 |= TIM_CR1_URS;
    TIMER->CR1 |= TIM_CR1_CEN; 
}