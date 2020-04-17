#ifndef __L1_RCC_H
#define __L1_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx.h"
#define RCC_AHBPeriph_GPIOC               RCC_AHBENR_GPIOCEN

 void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif
