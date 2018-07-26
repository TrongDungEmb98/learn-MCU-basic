#ifndef _clock_h_
#define _clock_h_

#include "hw_stm32f030r8t6.h"
void SystemInit(void);
void clock_enable(void);
void system_init(u32_t hsi_prediv, u32_t pullmux, u32_t pllsrc, u32_t ahb_div, u32_t system_source, u32_t apb1_div);

#endif   // _clock_h_