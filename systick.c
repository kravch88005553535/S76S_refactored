#include <stdint.h>
#include <stm32l073xx.h>
#include "stm32l0xx_hal.h"

volatile uint32_t systick_delay;

void systick_init(void)
{
    SysTick->LOAD = SysTick_LOAD_RELOAD_Msk / 500;
    NVIC_EnableIRQ(SysTick_IRQn);
    NVIC_SetPriority(SysTick_IRQn, 4);
}

void systick_delay_ms(uint32_t a_delay_ms)
{
    systick_delay = a_delay_ms;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    while (systick_delay) __ASM("nop");
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void)
{
    HAL_IncTick();
    systick_delay--;
}