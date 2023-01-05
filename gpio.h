#ifndef __GPIO_H__
#define __GPIO_H__

void gpio_init(void);


#define VOLTAGE_1V8             0b0000
#define VOLTAGE_1V9             0b0001
#define VOLTAGE_2V0             0b0010
#define VOLTAGE_2V1             0b0011
#define VOLTAGE_2V2             0b0100
#define VOLTAGE_2V3             0b0101
#define VOLTAGE_2V4             0b0110
#define VOLTAGE_2V5             0b0111
#define VOLTAGE_2V6             0b1000
#define VOLTAGE_2V7             0b1001
#define VOLTAGE_2V8             0b1010
#define VOLTAGE_2V9             0b1011
#define VOLTAGE_3V0             0b1100
#define VOLTAGE_3V1             0b1101
#define VOLTAGE_3V2             0b1110
#define VOLTAGE_3V3             0b1111

#define USART_PINS              GPIO_PIN_2|GPIO_PIN_3
#define ANTENNA_PIN             GPIO_PIN_1
#define CAPACITOR_PIN           GPIO_PIN_0
#define VOLTAGE_PINS            GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
#define SPI_PINS                GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_13
#define SPI_NSS_PIN             GPIO_PIN_12
#define SX1276_RESET_PIN        GPIO_PIN_10


#define diasble_capacitor();    GPIOA->ODR|=GPIO_ODR_OD0;
#define enable_capacitor();     GPIOA->ODR&=~GPIO_ODR_OD0;

#define setvoltage(voltage)     GPIOB->ODR&=0xFE1F; \
                                GPIOB->ODR |= voltage << GPIO_ODR_OD5_Pos;

#define SPI_NSS_ENABLE          GPIOB->ODR&=~GPIO_ODR_OD12;
#define SPI_NSS_DISABLE         GPIOB->ODR|=GPIO_ODR_OD12;

#endif //__GPIO_H__