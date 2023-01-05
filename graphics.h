#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <stdint.h>

void clearterminal(void);
void printaxes(uint8_t a_x_axis_offset, uint8_t a_y_axis_offset);
void printbargraph (int32_t a_adc_voltage, uint8_t a_iteration);
void printgraphics(void);

#endif //__GRAPHICS_H__