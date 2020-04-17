#include "stm32f0xx.h"
#include <stm32f0xx_gpio.h>
#include <stm32f0xx_rcc.h>
#include <stm32f0xx_tim.h>
#include <stm32f0xx_misc.h>


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

// chuong trinh con phuc vu ngat
void TIM3_IRQHandler (void)
   {
   static uint32_t time=0;
   //ngat xay ra khi CNT chuyen tu ARR->0 (dem len) va ngc lai 0 -> ARR (den xuong)
   if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
   {
	   GPIOC->ODR=0x300;
	   delay(40000);
	   GPIOC->ODR=0x0;
   }
   TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //xoa co ngat
  }

//Cau hinh Timer sinh ngat sau 1s ; f_CNT_CLK = 1KHz;
void TIMbase_Configuration (void)
 {
 NVIC_InitTypeDef NVIC_InitStructure;
 TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;

 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 TIM_TimeBaseStructure.TIM_Prescaler = 7999;// he so chia toc do counter
 TIM_TimeBaseStructure.TIM_Period = 999; //autoreload ARR
 TIM_TimeBaseStructure.TIM_ClockDivision = 0;
 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

 TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

 TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);  //cho phep ngat timer

 TIM_Cmd(TIM3, ENABLE); //cho phep timer

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
