#include "stm32f0xx.h"
#include"stm32f0xx_gpio.h"
#include"stm32f0xx_i2c.h"
//#include"stm32f0xx_misc.h"
#include"stm32f0xx_rcc.h"

// I2C Master

//pb6-pb6;  pb7-pb7: ket noi i2c

#define slave_addr    0x5A

void Delay( uint32_t nCount)
{
	while(nCount--)
	  {
	  }
	}
void InitLED(void)
{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void I2C_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	I2C_InitTypeDef   I2C_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  RCC_APB1PeriphClockCmd(RCC_APB1ENR_I2C1EN, ENABLE);

  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_1);
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_1);

/***************************** Master ******************************/

  	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_AnalogFilter=I2C_AnalogFilter_Enable;
    I2C_InitStructure.I2C_DigitalFilter=0x00;
    I2C_InitStructure.I2C_OwnAddress1 = 0x01;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_Timing = (uint32_t )0x00B01A4B;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C1, &I2C_InitStructure);

     /* I2C ENABLE */
    I2C_Cmd(I2C1, ENABLE);

    I2C_SlaveAddressConfig(I2C1,0x5A << 1);  //dia chi slave
}


int main(void)
{

InitLED();

I2C_Configuration();

int count=0, i=0;
unsigned char* st;
st="This string is sent from STM32 through I2C interface";

I2C1->CR2 &= (uint32_t)~((uint32_t) I2C_CR2_RD_WRN);  // I2C_CR2_RD_WRN=0 - write

 while (1)
	 {

	 for (i=0;i<strlen(st);i++){ //duyet tung ktu trong st

		 I2C_NumberOfBytesConfig(I2C1,1);
		 while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)==SET); //doi den khi bus roi

	     /* Send Start*/
		 GPIOC->ODR =0x200; //Bat LED 9
		 I2C_GenerateSTART(I2C1, ENABLE); //start

		 while(I2C_GetFlagStatus(I2C1, I2C_FLAG_TXE)==RESET); //doi cho den khi dem phat rong

		 GPIOC->ODR =0x100;  //bat LED 8

		 I2C_SendData(I2C1,st[i]); //truyen ki tu i

		 GPIOC->ODR =0x300; //bat 2 LED
		 Delay(400000);
	 }

	 count=count+1;

	 if (count==2){
		 I2C_GenerateSTOP(I2C1, ENABLE); //stop
		 while (I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF)==RESET);
	 }

	 Delay(400000);

	 GPIOC->ODR =0x000;
	 }
}





