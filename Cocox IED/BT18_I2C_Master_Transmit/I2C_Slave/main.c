#include "stm32f0xx.h"
#include"stm32f0xx_gpio.h"
#include"stm32f0xx_i2c.h"
#include"stm32f0xx_misc.h"
#include"stm32f0xx_rcc.h"
#include <stm32f0xx_usart.h>

/*	MASTER                    SLAVE
  PB6 --- I2C1_SCL		PB6 --- I2C2_SCL
  PB7 --- I2C1_SDA		PB7--- I2C2_SDA
*/

//Slaver
#define slave_addr    0X5A

GPIO_InitTypeDef  GPIO_InitStructure;
I2C_InitTypeDef   I2C_InitStructure;
NVIC_InitTypeDef  NVIC_InitStructure;

void Delay( uint32_t nCount)
{
  while(nCount--)
  {
  }
}
void InitLED(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);  //rcc.h

  // Configure the GPIO_LED pin
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;// 2 v 10
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void I2C_Configuration(void)
{

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1ENR_I2C1EN, ENABLE);


  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // enable pull up resistors
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_1);
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_1);

 // I2C1->TIMINGR  = (uint32_t )0x00B00000 ; /* (1) */
 // I2C1->CR1 = I2C_CR1_PE | I2C_CR1_ADDRIE | I2C_CR1_RXIE; /* (2) */
 // I2C1->OAR1  |= (uint32_t )(0x5A << 1); /* (3) */  // 7 bit address
 // I2C1->OAR1  |= I2C_OAR1_OA1EN ; /* (4) */


  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_AnalogFilter=I2C_AnalogFilter_Enable;
  I2C_InitStructure.I2C_DigitalFilter=0x00;
  I2C_InitStructure.I2C_OwnAddress1 = (0x5A << 1);

  I2C_InitStructure.I2C_Timing = (uint32_t )0x00B01A4B;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

  I2C_Init(I2C1, &I2C_InitStructure);

  I2C_Cmd(I2C1, ENABLE);

  I2C_ITConfig(I2C1, I2C_IT_ADDR, ENABLE);
  I2C_ITConfig(I2C1, I2C_IT_RXNE, ENABLE);

  /* Cau hinh ngat  */
   NVIC_InitStructure.NVIC_IRQChannel = I2C1_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

}
void I2C1_IRQHandler(void)
 {
	 if (I2C_GetITStatus(I2C1,I2C_IT_ADDR)) //khi match addr giua master va slave
	    {

		 I2C_AcknowledgeConfig(I2C1,ENABLE);
		 I2C_ClearITPendingBit(I2C1,I2C_IT_ADDR);
		 I2C_AcknowledgeConfig(I2C1,DISABLE);

		 GPIOC->ODR=0x200;
		 Delay(4000000);

		 GPIOC->ODR=0x000;
	    }

    if (I2C_GetITStatus(I2C1,I2C_IT_RXNE))
    {
    	I2C_AcknowledgeConfig(I2C1,ENABLE);
    	unsigned char ch = I2C_ReceiveData(I2C1);

     	GPIOC->ODR=0x100;
     	Send_Char(ch);

     	I2C_ClearITPendingBit(I2C1,I2C_IT_RXNE);
     	I2C_AcknowledgeConfig(I2C1,DISABLE);
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
int main(void)
{
	InitLED();

   I2C_Configuration();
   usart_setup();

   while (1) ;

}









