
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

		GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_1); //TIM3_CH3


		GPIOA_S.GPIO_Pin    = GPIO_Pin_7;

		GPIOA_S.GPIO_Mode    = GPIO_Mode_AF;
		GPIOA_S.GPIO_OType = GPIO_OType_PP;
		GPIOA_S.GPIO_PuPd    = GPIO_PuPd_NOPULL;
		GPIOA_S.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOA, &GPIOA_S);

	/* TIM3 clock enable */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

		TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;

	 TIM_TimeBaseStructure.TIM_Prescaler = 7999;// he so chia toc do counter
	 TIM_TimeBaseStructure.TIM_Period = 65535; //autoreload ARR
	 TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	 TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);


	 TIM_OCInitTypeDef  TIM_OCI_S;


	 TIM_OCI_S.TIM_OCMode = TIM_OCMode_PWM1;

	 //TIM3_CCMR1 - OC2M :
	 //110: PWM mode 1 - In upcounting, channel 2 is active as long as TIMx_CNT<-TIMx_CCR1
	 //else inactive. In downcounting, channel 1 is inactive (OC1REF=‘0) as long as
	 //TIMx_CNT>TIMx_CCR1 else active (OC1REF=1).

	 //111: PWM mode 2 - In upcounting, channel 2 is inactive as long as TIMx_CNT<-TIMx_CCR1
	 //else active. In downcounting, channel 1 is active as long as TIMx_CNT>TIMx_CCR1 else inactive.

	 TIM_OCI_S.TIM_OutputState = TIM_OutputState_Enable; //enable/disable
	 TIM_OCI_S.TIM_OCPolarity = TIM_OCPolarity_High;  //Tin hieu ra tren channel Hight/Low
	 TIM_OCI_S.TIM_Pulse = 65534;  //gia tri dc nap vao TIM3_CCR: 0x0000 and 0xFFFF

	  /* Channel2 - */
	 TIM_OC2Init (TIM3, &TIM_OCI_S);



	/* TIM enable counter */
	TIM_Cmd(TIM3, ENABLE);

	/* Remove all interrupt flag */
	TIM3->SR=0;

	TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);
	TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);

	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the TIM3 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}
	void TIM3_IRQHandler(void)
	{
	if(TIM_GetITStatus(TIM3, TIM_IT_CC2) == SET)
	{
	/* Get the Input Capture value */
		int i=0, j;
		unsigned int val;
		unsigned char mod;
		unsigned char data[100];

		val = TIM_GetCapture2(TIM3);//val1=6500; val2=100

		GPIOC->ODR=0x300;

		if (val==0)
					Send_String("CNT:0");
		else{
			while(val!=0){
				mod=val%10;
				val=val/10;
				data[i]= (char)(mod+48);
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

	/* Clear TIM3 Capture compare interrupt pending bit */
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

/*
 * void timer_pwm_init (void)
{
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  // always initialise local variables before use
  TIM_OCStructInit (&TIM_OCInitStructure);

  // Common settings for all channels
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_Pulse = 0;

  // Channel2 - ORANGE LED
  TIM_OC2Init (TIM3, &TIM_OCInitStructure);

  // Channel3 - RED LED
  TIM_OC3Init (TIMER, &TIM_OCInitStructure);

  // Channel4 - BLUE LED
  // make this the opposite polarity to the other two
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OC4Init (TIMER, &TIM_OCInitStructure);
}
*/

//https://stm32f4-discovery.net/2014/05/stm32f4-stm32f429-discovery-pwm-tutorial/
