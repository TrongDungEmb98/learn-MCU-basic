#include "stm32f0xx.h"
#include <stm32f0xx_gpio.h>
#include <stm32f0xx_rcc.h>
#include <stm32f0xx_tim.h>
#include <stm32f0xx_misc.h>
//#include <stm32f0xx_syscfg.h>

void InitLED(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);//rcc.h

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;// 2 v 10
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}


void TIM3_IRQHandler (void)
   {
   static uint32_t time=0;
   if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
   {
	   GPIOC->ODR=0x300;
	   delay(40000);
	   GPIOC->ODR=0x0;
   }
   TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
   }

void TIMbase_Configuration (void)
 {
 NVIC_InitTypeDef NVIC_InitStructure;
 TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;

 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 TIM_TimeBaseStructure.TIM_Prescaler = 3999;
 TIM_TimeBaseStructure.TIM_Period = 29999;
 TIM_TimeBaseStructure.TIM_ClockDivision = 0;
 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
 TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
 TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
 TIM_Cmd(TIM3, ENABLE);


 NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
 NVIC_InitStructure.NVIC_IRQChannelPriority=0;

 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 NVIC_Init(&NVIC_InitStructure);
 }

void delay(unsigned int x){
	int i=0;
	for (i=0;i<x;i++);

}
void  main(){
	InitLED();
   TIMbase_Configuration();
   while(1);
  }
