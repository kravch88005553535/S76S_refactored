#ifndef __ADC_H__
#define __ADC_H__

#include <stdint.h>

void adc_init(void);
void start_adc(void);
uint32_t getadcvoltage(void);

#endif //__ADC_H__