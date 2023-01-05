#include "stm32l0xx_ll_gpio.h"
#include "gpio.h"

void gpio_init(void)
{
    GPIO_InitTypeDef gpio_initstruct = {};
    gpio_initstruct.Pin = USART_PINS;
    gpio_initstruct.Mode = GPIO_MODE_AF_PP;
    gpio_initstruct.Pull = GPIO_PULLUP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio_initstruct.Alternate = GPIO_AF4_USART2;
    HAL_GPIO_Init(GPIOA,&gpio_initstruct);
    
    gpio_initstruct.Pin = ANTENNA_PIN;
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_initstruct.Pull = GPIO_PULLUP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio_initstruct.Alternate = 0;
    HAL_GPIO_Init(GPIOA,&gpio_initstruct);
    
//    gpio_initstruct.Pin = CAPACITOR_PIN;
//    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_OD;
//    gpio_initstruct.Pull = GPIO_NOPULL;
//    gpio_initstruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    gpio_initstruct.Alternate = 0;
//    HAL_GPIO_Init(GPIOA,&gpio_initstruct);
//    enable_capacitor();
    
    gpio_initstruct.Pin = VOLTAGE_PINS;
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_initstruct.Pull = GPIO_PULLUP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio_initstruct.Alternate = 0;
    HAL_GPIO_Init(GPIOB,&gpio_initstruct);
    setvoltage(VOLTAGE_3V3);
    
    gpio_initstruct.Pin = SPI_PINS;
    gpio_initstruct.Mode = GPIO_MODE_AF_PP;
    gpio_initstruct.Pull = GPIO_PULLDOWN;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_initstruct.Alternate = GPIO_AF0_SPI2;
    HAL_GPIO_Init(GPIOB,&gpio_initstruct);
    
    gpio_initstruct.Pin = SPI_NSS_PIN;
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_initstruct.Pull = GPIO_PULLUP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio_initstruct.Alternate = 0;
    HAL_GPIO_Init(GPIOB,&gpio_initstruct);
    SPI_NSS_DISABLE;

    gpio_initstruct.Pin = SX1276_RESET_PIN;
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_initstruct.Pull = GPIO_PULLUP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio_initstruct.Alternate = 0;
    HAL_GPIO_Init(GPIOB,&gpio_initstruct);

//    GPIO_InitTypeDef adc_port_initstruct = {};
//    adc_port_initstruct.Pin = GPIO_PIN_1;
//    adc_port_initstruct.Mode = GPIO_MODE_ANALOG;
//    adc_port_initstruct.Pull = GPIO_NOPULL;
//    adc_port_initstruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    HAL_GPIO_Init(GPIOB,&adc_port_initstruct);
}