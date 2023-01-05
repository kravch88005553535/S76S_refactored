#include <stm32l073xx.h>
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_adc.h"
#include "adc_constants.h"

void adc_init(void)
{    
    DMA_HandleTypeDef dma_handletypedef = {};
    ADC_ChannelConfTypeDef adc_channelconfstruct;
    adc_channelconfstruct.Channel = ADC_CHANNEL_17;
    adc_channelconfstruct.Rank = ADC_RANK_CHANNEL_NUMBER;
    
    ADC_OversamplingTypeDef adc_oversamplinginitstruct = {};
    adc_oversamplinginitstruct.Ratio = ADC_OVERSAMPLING_RATIO_2;
    adc_oversamplinginitstruct.RightBitShift = ADC_RIGHTBITSHIFT_NONE;
    adc_oversamplinginitstruct.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
    
    ADC_InitTypeDef adc_initstruct = {};
    adc_initstruct.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    adc_initstruct.Resolution =  ADC_RESOLUTION_12B;
    adc_initstruct.DataAlign = ADC_DATAALIGN_RIGHT;
    adc_initstruct.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
    adc_initstruct.EOCSelection = ADC_EOC_SINGLE_CONV;
    adc_initstruct.LowPowerAutoWait = DISABLE;
    adc_initstruct.LowPowerAutoPowerOff = DISABLE; 
    adc_initstruct.ContinuousConvMode = DISABLE;
    adc_initstruct.DiscontinuousConvMode = ENABLE;
    adc_initstruct.ExternalTrigConv = ADC_SOFTWARE_START;
    adc_initstruct.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    adc_initstruct.DMAContinuousRequests = DISABLE;
    adc_initstruct.Overrun = ADC_OVR_DATA_OVERWRITTEN;
    adc_initstruct.LowPowerFrequencyMode = DISABLE;
    adc_initstruct.SamplingTime = ADC_SAMPLETIME_79CYCLES_5;
    adc_initstruct.OversamplingMode = DISABLE;
    adc_initstruct.Oversample = adc_oversamplinginitstruct;
   
    ADC_HandleTypeDef adc_handlestruct = {};
    adc_handlestruct.Instance = ADC1;
    adc_handlestruct.Init = adc_initstruct;
    adc_handlestruct.DMA_Handle = &dma_handletypedef;
    adc_handlestruct.Lock = HAL_UNLOCKED;
    adc_handlestruct.State = 0;
    adc_handlestruct.ErrorCode = 0;
    HAL_ADC_Init(&adc_handlestruct);
    
    HAL_ADC_ConfigChannel(&adc_handlestruct, &adc_channelconfstruct);
    HAL_ADCEx_Calibration_Start(&adc_handlestruct,ADC_SINGLE_ENDED);
    HAL_ADC_Start(&adc_handlestruct);    
}

void start_adc(void)
{
    ADC1->CR |= ADC_CR_ADSTART;
}

uint32_t getadcvoltage()
{
    const uint16_t* const vrefint_cal = ((uint16_t*)(ADC_VREFINT_ADDRESS));
    return ADC_FACTORY_VREFINT_CALIBRATION_VOLTAGE * (*vrefint_cal) / ADC_DATA_REGISTER_VALUE;
}