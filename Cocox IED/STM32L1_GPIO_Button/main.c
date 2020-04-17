#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"  // thu vien cau hinh chan vao ra
#include "stm32l1xx_rcc.h"

void delay(int ticks);
void delayMS(unsigned int ms);

int main(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 GPIO_InitTypeDef  GPIO_InitStructure1;
	 /* Enable the GPIO_LED Clock */
	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	  GPIO_InitStructure.GPIO_Mode = 0x1000 ; //GPIO_Mode_OUT;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz; // 2 v 10



	  //GPIO_Init(GPIOC, &GPIO_InitStructure);

	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	  	  GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_0;
	  	  GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IN;
	  	  GPIO_InitStructure1.GPIO_OType = GPIO_OType_PP;
	  	  GPIO_InitStructure1.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  	  GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_40MHz; // 2 v 10

	  	  GPIO_Init(GPIOA, &GPIO_InitStructure1);

    while(1)
    {

    	if (GPIOA->IDR & 0x1)
			GPIOC->ODR= 0x0300;
			delayMS(10000);
			GPIOC->ODR= 0x00;
			//delayMS(10000);
    }
}

void delay(int ticks)
	{
	  while(ticks--);
	}
void delayMS(unsigned int ms){
	    unsigned int x;
	    for(x=0;x<ms;x++)
	    	delay(600);
	    }
