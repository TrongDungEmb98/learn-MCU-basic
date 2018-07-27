#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "stm32lib.h"

extern void init_systick(void);
extern void start_timer(unsigned int value);
extern unsigned int get_state_timer(void);
extern void delay_timer_ms(unsigned int value);

#endif	//_SYSTICK_H_