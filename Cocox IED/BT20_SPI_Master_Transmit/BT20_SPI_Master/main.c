
#include <stm32f0xx.h>
#include <stm32f0xx_spi.h>
#include <stm32f0xx_gpio.h>
#include <stm32f0xx_rcc.h>
#include <stm32f0xx_misc.h>
#include <stm32f0xx_usart.h>

/*
   * cach noi day - dau thang
   * SPI1          		SPI2
   * PB12_SPI1_NSS		PB12-SPI2_NSS
   * PB13-SPI1_SCK		PB13-SPI2_SCK
   * PB14-SPI1_MISO		PB14-SPI2_MISO
   * PB15-SPI1_MOSI		PB15-SPI2_MOSI
   */

void Delay( uint32_t nCount)
{
	while(nCount--)
	  {
	  }
	}
void InitLED(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void init_SPI2(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStruct;

	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	 GPIO_Init(GPIOB, &GPIO_InitStructure);

	 GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_0);
	 GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_0);
	 GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_0);

	// enable clock for used IO pins
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);


	/*SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // set to full duplex mode, seperate MOSI and MISO lines
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;     // transmit in master mode
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b; // one packet of data is 8 bits wide
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;        // clock is low when idle
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;      // data sampled at first edge
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft; // set the NSS management to internal and pull internal NSS high
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; // SPI frequency is APB2 frequency / 4
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;// data is transmitted MSB first
	SPI_SSOutputCmd(SPI2,ENABLE);
	SPI_Init(SPI2, &SPI_InitStruct);
	SPI_Cmd(SPI2, ENABLE); */

	 SPI2->CR1 |= SPI_CR2_FRXTH;
	 SPI2->CR1 = SPI_CR1_MSTR | SPI_CR1_BR;
	 SPI2->CR2 = SPI_CR2_SSOE | SPI_CR2_RXNEIE | SPI_CR2_FRXTH
	            | SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0 ;
	 SPI2->CR1 |= SPI_CR1_SPE;


	NVIC_InitTypeDef  NVIC_InitStructure;
	  //cau hinh ngat cho slave khi nhan du lieu
	 NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
	 NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_Init(&NVIC_InitStructure);

	 SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, ENABLE);
	    //ket thuc cau hinh ngat cho spi2

}

void SPI2_IRQHandler(void)
 {
    if (SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_RXNE) != RESET)
    {

      unsigned char ch =  SPI_ReceiveData8(SPI2);
      Send_Char(ch);
      Delay(400000);
      SPI_I2S_ClearFlag(SPI2, SPI_I2S_IT_RXNE);
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
	init_SPI2();
	usart_setup();
	InitLED();
	unsigned char* st; unsigned i;
	st="This string is sent from SPI Master\n";

	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
    while(1)
    {
    	GPIOC->ODR=0x200;

    	for (i=0;i<strlen(st);i++){

    		while(!(SPI2->SR & SPI_I2S_FLAG_TXE));

    		SPI_SendData8(SPI2,st[i]);
    		Delay(400000);

    	}
    	Delay(400000);
    	GPIOC->ODR=0x100;
    	Delay(400000);

    }
}
