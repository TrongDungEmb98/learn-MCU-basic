#include <stm32f0xx_gpio.h>
#include <stm32f0xx_usart.h>
#include <stm32f0xx_rcc.h>
#include <stm32f0xx_misc.h> //NVIC
//STM32F051R6
void usart_setup(void)
{

	// PA9 - Tx; PA10-Rx
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
  USART1_S.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART1_S.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART1_S);
  USART_Cmd(USART1,ENABLE);

  /* Enable USART1 IRQ BT12*/

  NVIC_InitTypeDef NVIC_S;
  USART_ITConfig(USART1, USART_IT_TXE, ENABLE); //cho phep ngat khi dem truyen rong
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // cho phep ngat khi nhan dc mot ky tu

  NVIC_S.NVIC_IRQChannel = USART1_IRQn;    // cho phep ngay USART1
  NVIC_S.NVIC_IRQChannelPriority = 0;
  NVIC_S.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_S);

}
void Send_Char(unsigned char data)
{
	  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
	  USART_SendData(USART1,data);

}

void Send_String(unsigned char str[100]){

	int i;
	for (i=0;i<strlen(str); i++){
		Send_Char(str[i]);

	}

}

unsigned char  Received_Char()
{
	unsigned char ch;

	while((USART1->ISR & USART_ISR_RXNE) == RESET);
	  	  ch = (char) USART1->RDR;
	return ch;
}

unsigned char st[100];
void Received_String()
{

	int i=0;
	st[0]='\0';
	while (1){
	st[i]=Received_Char();
	if ((st[i] =='x'))
		break;
	i++;
	}

}

void delay(unsigned int x){
	int i=0;
	for (i=0;i<x;i++);

}
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

unsigned char st_sd[100] ="\nHello, this string is sent from STM32F0";
unsigned char st_re[100]; //vung dem nhan xau ky tu tu may tinh
int  i=0, i1=0;

void USART1_IRQHandler(void)
{
	//Ngat xay ra neu dem phat rong
	if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
	{
		GPIOC->ODR=0x200;
		if (i<strlen(st_sd)){
			Send_Char(st_sd[i]);
			i++;
		}
		USART1->ISR &= ~USART_FLAG_TXE; //xoa co ngat

	}


	//Ngat xay ra khi nhan dc mot ky tu ~ dem nhan du lieu khac rong
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		unsigned char ch=Received_Char();
		GPIOC->ODR=0x100;
		if (ch!='x'){
			st_re[i1]=ch;
			i1++;
		}
		if (ch=='x'){
		Send_String("\nReceived: ");
		Send_String(st_re);
		i1=0;

		}

		USART1->ISR &= ~USART_FLAG_RXNE;  //Xoa co ngat
	}
}


main(){

	InitLED();
	usart_setup();


	//Send_String("\nHello, this string is sent from STM32F0");

	while(1);

}
