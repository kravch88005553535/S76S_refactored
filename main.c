#include <stm32l073xx.h>

#include "stm32l0xx_hal.h"
#include "systick.h"
#include "rcc.h"
#include "gpio.h"
#include "uart.h"
#include "dma.h"
#include "adc.h"
#include "timers.h"
#include "spi.h"
#include "sx1276.h"
#include "interrupts.h"

//#include "sx1276.h"

int main (void)	
{

HAL_Init();
systick_init();
rcc_init();  
gpio_init();

dma_init();
adc_init();
timer_init();
spi_init();
uart_init();

sx1276_init();

    SetupInterrupts();
    EnableInterrupts();

    while (1)
    {
    }
}