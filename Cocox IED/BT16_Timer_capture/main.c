
#include "stm32f0xx.h"
#include <stm32f0xx_gpio.h>
#include <stm32f0xx_rcc.h>
#include <stm32f0xx_tim.h>
#include <stm32f0xx_misc.h>
#include <stm32f0xx_usart.h>


/*
 * Chuong trinh Capture gia tri CNT (counter) cua Timer3 tren channel Capture/Compare 2 su dung Boarch STM32F0;
 * Gia tri doc duoc duoc gui qua USART1 len may tinh
 *
 */

void delay(unsigned int x){
	int i=0;
	for (i=0;i<x;i++);

}
void InitLED(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);//rcc.h

  // Configure the GPIO_LED pin
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;// 2 v 10
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void TIME_Capture(){
		// TIM3_CH2 -- PA7
		GPIO_InitTypeDef GPIOA_S ;

		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

		GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_1); //Chuyen chuc nang cho chan PA7 --> TIM3_CH2
		GPIOA_S.GPIO_Pin    = GPIO_Pin_7;

		GPIOA_S.GPIO_Mode    = GPIO_Mode_AF;
		GPIOA_S.GPIO_OType = GPIO_OType_PP;
		GPIOA_S.GPIO_PuPd    = GPIO_PuPd_NOPULL;
		GPIOA_S.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOA, &GPIOA_S);

	// TIM3 clock enable
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	 TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;

	 TIM_TimeBaseStructure.TIM_Prescaler = 7999;// he so chia toc do counter
	 TIM_TimeBaseStructure.TIM_Period = 999; //autoreload ARR
	 TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //dem tu 0->TIM3->ARR; dem xuong TIM3->ARR-> 0

	 TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	 //config channel 2 - Timer 3
	 TIM_ICInitTypeDef IC_CHS;
	 IC_CHS.TIM_Channel = TIM_Channel_2;
	 IC_CHS.TIM_ICPolarity = TIM_ICPolarity_Rising; //capture khi tang 0->1
	 IC_CHS.TIM_ICSelection = TIM_ICSelection_DirectTI;  //!< TIM Input 1, 2, 3 or 4 is selected to be connected to IC1, IC2, IC3 or IC4, respectively
	 IC_CHS.TIM_ICPrescaler = TIM_ICPSC_DIV1; //moi khi PA7 chuyen 0->1 --> thuc hien capture
	 //!< Capture performed each  time an edge is detected on the capture input. ; DIV2 ~ capture every 2 edges ...
	 IC_CHS.TIM_ICFilter = 0x0;

	 TIM_ICInit(TIM3, &IC_CHS);

	//TIM enable counter
	TIM_Cmd(TIM3, ENABLE);

	// Remove all interrupt flags
	TIM3->SR=0;

	TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);// cho phep ngat channel 2
	TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);

	NVIC_InitTypeDef NVIC_InitStructure;

	// Enable the TIM3 global Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}
	void TIM3_IRQHandler(void)
	{
	if(TIM_GetITStatus(TIM3, TIM_IT_CC2) == SET)
	{
	// Get the Input Capture value
		int i=0, j;
		unsigned int val;
		unsigned char mod;
		unsigned char data[100];

		val = TIM_GetCapture2(TIM3); //Doc gia CCR ; moi lan capture TIM3->CNT-> TIM3->CCR

		/* TM_count ++ */

		GPIOC->ODR=0x300;

		if (val==0)
			Send_String("CNT:0");
		else{
			while(val!=0){
				mod=val%10;  //val = 234 /10 =23; mod = 234%10=4
				val=val/10;
				data[i]= (char)(mod+48);  //48~ ma ASCII cua 0, 49 ~ 1,...
				i++;
				//Send_Char((char)(mod+48));
			}

			Send_String("\nCNT: ");

			for (j=i-1;j>=0;j--){
				Send_Char(data[j]);
			}
		}
	//Send_String("OK");
	delay(400000);
	GPIOC->ODR=0x000;

	// Clear TIM3 Capture compare interrupt pending bit
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);

	}
	}

	void usart_setup(void)
	{

		//USART1: PA9 - Tx <-> Rx (USB TTL) ; PA10-Rx <-> Tx (USB TTL)
		GPIO_InitTypeDef GPIOA_S ;
		USART_InitTypeDef USART1_S;

		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1); //USART
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);//

		GPIOA_S.GPIO_Pin    = GPIO_Pin_10 | GPIO_Pin_9;
		GPIOA_S.GPIO_Speed = GPIO_Speed_50MHz;
		GPIOA_S.GPIO_Mode    = GPIO_Mode_AF;
		GPIOA_S.GPIO_OType = GPIO_OType_PP;
		GPIOA_S.GPIO_PuPd    = GPIO_PuPd_UP;
		GPIO_Init(GPIOA, &GPIOA_S);


	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

	  USART1_S.USART_BaudRate = 115200;
	  USART1_S.USART_WordLength = USART_WordLength_8b;
	  USART1_S.USART_StopBits = USART_StopBits_1;
	  USART1_S.USART_Parity = USART_Parity_No;
	  USART1_S.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //ko dung CTS/RTS
	  USART1_S.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	  USART_Init(USART1, &USART1_S);

	  USART_Cmd(USART1,ENABLE);
	}
	void Send_Char(unsigned char data)
	{
		  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
		  USART_SendData(USART1,data);

	}

	void Send_String(unsigned char str[100]){ //char * x; char x[100] ;

		int i;
		for (i=0;i<strlen(str); i++){
			Send_Char(str[i]);

		}

	}



int main(void)
{
	TIME_Capture();
	usart_setup();
	InitLED();

    while(1)
    {
    }
 }



//https://community.st.com/s/question/0D50X00009Xke3CSAR/stm32f10x-input-capture

//https://github.com/yhyuan/STM32-Examples/blob/master/6-M3-PWM%20Input%20Capture/USER/main.c
