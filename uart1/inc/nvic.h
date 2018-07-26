#ifndef _nvic_h_
#define _nvic_h_

#include "hw_stm32f030r8t6.h"

extern volatile unsigned char rx_data;
extern volatile unsigned char command[5];
extern volatile unsigned char num_char; 

void Reserved_IRQHandler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void EXTI0_IRQHandler(void);
void inti_interrupt(void);
void USART1_IRQHandler(void);



#endif // _nvic_h_