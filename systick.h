#ifndef __SYSTICK_H__
#define __SYSTICK_H__
#include <stdint.h>


void systick_init(void);
void systick_delay_ms(uint32_t a_delay_ms);

#endif //__SYSTICK_H__