#include <stm32l073xx.h>
#include "stm32l0xx_ll_rcc.h"

void rcc_init(void)
{    
    RCC_PLLInitTypeDef rcc_pllinitstruct = {};
    rcc_pllinitstruct.PLLDIV = RCC_PLLDIV_3;
    rcc_pllinitstruct.PLLMUL = RCC_PLLMUL_4;
    rcc_pllinitstruct.PLLSource = RCC_PLLSOURCE_HSE;
    rcc_pllinitstruct.PLLState = RCC_PLL_ON;

    RCC_OscInitTypeDef rcc_oscillatorinitstruct = {};
    rcc_oscillatorinitstruct.HSI48State = RCC_HSI48_OFF;
    rcc_oscillatorinitstruct.HSIState = RCC_HSI_OFF;
    rcc_oscillatorinitstruct.LSEState = RCC_LSE_OFF;
    rcc_oscillatorinitstruct.MSIState = RCC_MSI_OFF;
    rcc_oscillatorinitstruct.HSEState = RCC_HSE_ON;
    rcc_oscillatorinitstruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    rcc_oscillatorinitstruct.PLL = rcc_pllinitstruct;
    HAL_RCC_OscConfig(&rcc_oscillatorinitstruct);

    RCC_ClkInitTypeDef rcc_clockinitstruct = {};
    rcc_clockinitstruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
    rcc_clockinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    rcc_clockinitstruct.APB1CLKDivider = RCC_HCLK_DIV1;
    rcc_clockinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
    rcc_clockinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    HAL_RCC_ClockConfig(&rcc_clockinitstruct,FLASH_LATENCY_1);

    LL_RCC_MSI_Disable();

#if defined(DEBUG)
   RCC->APB2ENR |= RCC_APB2ENR_DBGEN; 
   DBGMCU->APB1FZ |= DBGMCU_APB1_FZ_DBG_TIM2_STOP;
#endif //DEBUG

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_ADC1_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();
    __HAL_RCC_TIM2_CLK_ENABLE();
    __HAL_RCC_SPI2_CLK_ENABLE();
}  