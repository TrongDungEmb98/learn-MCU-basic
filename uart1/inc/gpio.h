#ifndef _gpio_h_
#define _gpio_h_

#include "hw_stm32f030r8t6.h"

void Init_Led(void);
void Init_Button(void);
void led_on(unsigned int led, const unsigned int registers);
void led_off(unsigned int led, const unsigned int registers);



#endif	// _gpio_h_