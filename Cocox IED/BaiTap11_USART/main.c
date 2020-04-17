#include <stm32f0xx_gpio.h>
#include <stm32f0xx_usart.h>
#include <stm32f0xx_rcc.h>

//  STM32F051R6
/*
 *
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
	//st[0]='\0' ;
	int i=0;
	while (1){
	st[i]=Received_Char();

	if ((st[i] =='x'))  //'\r', '\n' - ki tu xuong dong
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

  // Configure the GPIO_LED pin
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;// 2 v 10
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

main(){
	unsigned char ch;
	InitLED();
	usart_setup();

	while(1){

        Send_String("\nHello, this string is sent from STM32F0");

		ch = Received_Char();

		if (ch=='a'){
			GPIOC->ODR=0x300;
			Send_String("\nSTM32F0 received: ");
			Send_Char(ch);
			delay(400000);
		}

		GPIOC->ODR=0x00;

		Received_String();
		Send_String("\nSTM32F0 received:");
		Send_String(st);
}
}
*/

//==============================K15A-===========================================
//Trong Dung

//  STM32F051R6
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
	//st[0]='\0' ;
	int i=0;
	while (1){
	st[i]=Received_Char();

	if ((st[i] =='x'))  //'\r', '\n' - ki tu xuong dong
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

main(){
	unsigned char ch;
	InitLED();
	usart_setup();

	while(1){

        Send_String("Lop KTMT K15A");

		ch = Received_Char();

		if (ch=='a'){
			GPIOC->ODR=0x300;
			Send_String("\nSTM32F0 received: ");
			Send_Char(ch);
			delay(400000);
		}

		GPIOC->ODR=0x00;

		Received_String();
		Send_String("\nSTM32F0 received:");
		Send_String(st);
}
}
/*
//Pham Van Hieu
#include <stm32f0xx_gpio.h>
#include <stm32f0xx_usart.h>
#include <stm32f0xx_rcc.h>

// STM32F051R6
void usart_setup(void)
{

//USART1: PA9 - Tx <-> Rx (USB TTL) ; PA10-Rx <-> Tx (USB TTL)
GPIO_InitTypeDef GPIOA_S ;
USART_InitTypeDef USART1_S;

RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1); //USART
GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);//

GPIOA_S.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_9;
GPIOA_S.GPIO_Speed = GPIO_Speed_50MHz;
GPIOA_S.GPIO_Mode = GPIO_Mode_AF;
GPIOA_S.GPIO_OType = GPIO_OType_PP;
GPIOA_S.GPIO_PuPd = GPIO_PuPd_UP;
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

unsigned char Received_Char()
{
unsigned char ch;

while((USART1->ISR & USART_ISR_RXNE) == RESET);
ch = (char) USART1->RDR;
return ch;
}

unsigned char st[100];

void Received_String()
{
//st[0]='\0' ;

int i=0;
while (1){
st[i]=Received_Char();

if ((st[i] =='x')) //'\r', '\n' - ki tu xuong dong
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
GPIO_InitTypeDef GPIO_InitStructure;

RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);//rcc.h

// Configure the GPIO_LED pin
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;// 2 v 10
GPIO_Init(GPIOC, &GPIO_InitStructure);
}

main(){
unsigned char ch;
InitLED();
usart_setup();

while(1){

Send_String("Lop KTMT K15A");

ch = Received_Char(); //Cho nhan 1 ky tu tu may tinh

if (ch=='a'){
	GPIOC->ODR=0x300;
	Send_String("\nSTM32F0 received: ");

	Send_Char(ch);
	delay(400000);
}

GPIOC->ODR=0x00;

Received_String(); //Cho nhan 1 xau ky tu
Send_String("\nSTM32F0 received:");
Send_String(st);
}
}

//-----------------------------K16A----------------------------------------

//Tien Dung

/*

int usart_setup(void)
{
GPIO_InitTypeDef GPIOA_S ;
USART_InitTypeDef USART1_S ;
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);

GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,GPIO_AF_1);
GPIO_PinAFConfig(GPIOA, GPIO_PinSource10,GPIO_AF_1);

GPIOA_S.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_9;
GPIOA_S.GPIO_Speed = GPIO_Speed_50MHz;
GPIOA_S.GPIO_Mode = GPIO_Mode_AF;
GPIOA_S.GPIO_OType = GPIO_OType_PP;
GPIOA_S.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Init(GPIOA, &GPIOA_S);


RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
USART1_S.USART_BaudRate = 9600;
USART1_S.USART_WordLength = USART_WordLength_8b;
USART1_S.USART_StopBits = USART_Parity_No;
USART1_S.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
USART1_S.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
USART_Init(USART1, &USART1_S);
USART_Cmd(USART1,ENABLE);

}


void Send_char(unsigned char data){
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	USART_SendData(USART1,data);
}
void SendString(unsigned char str[100]){

	int i;
	for(i=0;i<strlen(str);i++){
		Send_char(str[i]);

	}
}
unsigned char Received_char(){
	unsigned char ch;
	while((USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET));
	ch=(char) USART1->RDR;
	return ch;
}


unsigned char st[100];
void Received_String(){
	int i=0;
	while (1){
		st[i]=Received_char();
		if((st[i]=='x'))
			break;
		i++;
}
}
void delay(unsigned int x){
int i=0;
for(i=0;i<x;i++){
}
}

void InitLED(void){
GPIO_InitTypeDef GPIO_InitStructure ;
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);


GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOC, &GPIO_InitStructure);
}


main(){
unsigned char ch;
InitLED();
usart_setup();
while(1){
SendString("\nhelo, this string is sent from stm32f0");
ch = Received_char();
if(ch=='a'){
GPIOC->ODR=0x300;
SendString("stm32f0 received: ");
Send_char(ch);
delay(4000);
}
GPIOC->ODR=0x00;
Received_String("stm32f0 received: ");
Send_char(ch);
}
}
*/

// Phuong

/*int usart_setup(void)
{
//USART1: PA9 -Tx <-> Rx(USB TTL); PA10-Rx<->Tx (USB TTL)
GPIO_InitTypeDef GPIOA_S ;
USART_InitTypeDef USART1_S ;

RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,GPIO_AF_1);
GPIO_PinAFConfig(GPIOA, GPIO_PinSource10,GPIO_AF_1);

GPIOA_S.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_9;
GPIOA_S.GPIO_Speed = GPIO_Speed_50MHz;
GPIOA_S.GPIO_Mode = GPIO_Mode_AF;
GPIOA_S.GPIO_OType = GPIO_OType_PP;
GPIOA_S.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Init(GPIOA, &GPIOA_S);

RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
USART1_S.USART_BaudRate = 9600;
USART1_S.USART_WordLength = USART_WordLength_8b;
USART1_S.USART_StopBits = USART_Parity_No;
USART1_S.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
USART1_S.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
USART_Init(USART1, &USART1_S);

USART_Cmd(USART1,ENABLE);

}


void Send_Char (unsigned char data){
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	USART_SendData(USART1,data);
}


void SendString(unsigned char str[100]){
int i;
for(i=0;i< strlen(str);i++){
	Send_Char(str[i]);


}
}

unsigned char Received_Char(){
unsigned char ch;
while((USART1->ISR & USART_ISR_RXNE)==RESET);
ch =(char) USART1 ->RDR;
return ch;
}


unsigned char st[100];
void Received_String(){
int i=0;
while(1){
st[i]=Received_Char();
if (st[i]== 'x')
	break;
i++;

}
}

void InitLED(void){
GPIO_InitTypeDef GPIO_InitStructure;

RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 2 v 10

GPIO_Init(GPIOC,&GPIO_InitStructure);
}
void delay(unsigned int x){
	int i=0;
	for(i=0;i<x;i++){
	}
}
main(){
	unsigned char ch;
	InitLED();
	usart_setup();
	while(1){

		SendString("Hello, PC, \n");

		ch=Received_Char();

		if (ch=='a') {
			GPIOC->ODR=0x300;
			SendString("\nSTM32F0 received a char! ");
			delay(400000);
		}
GPIOC->ODR=0x00;

Received_String();
SendString("\nSTM32F0 received:");
SendString(st);
}



}

*/
//Huy
/*void usart(void)
{
	//PA9 TX; PA10 RX
	GPIO_InitTypeDef init;
	USART_InitTypeDef usart;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_1);

	init.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_9;
	init.GPIO_Speed=GPIO_Speed_50MHz;
	init.GPIO_Mode=GPIO_Mode_AF;
	init.GPIO_OType=GPIO_OType_PP;
	init.GPIO_PuPd=GPIO_PuPd_UP;

	GPIO_Init(GPIOA,&init);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

	usart.USART_BaudRate=9600;
	usart.USART_WordLength=USART_WordLength_8b;
	usart.USART_StopBits=USART_StopBits_1;
	usart.USART_Parity=USART_Parity_No;
	usart.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	usart.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1,&usart);

	USART_Cmd(USART1,ENABLE);
}
void initLed(void)
{
	GPIO_InitTypeDef init;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);

	init.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	init.GPIO_Mode=GPIO_Mode_OUT;
	init.GPIO_OType=GPIO_OType_PP;
	init.GPIO_PuPd=GPIO_PuPd_NOPULL;
	init.GPIO_Speed=GPIO_Speed_50MHz;

	GPIO_Init(GPIOC,&init);
}
void delay(int t){
	while(t--);
}
void send_char(unsigned char data)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	USART_SendData(USART1,data);
}
void send_string(unsigned char st[100])
{
	int i;
	//while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	//	while(*str)
	//	{
	//		send(*str++);
	//	}
	for (i=0;i<strlen(st);i++){
		send_char(st[i]);
	}
}
unsigned char receive_char()
{
	unsigned char ch;
	while((USART1->ISR & USART_ISR_RXNE) == RESET);

	ch=(char)(USART1->RDR);
	return ch;
}
unsigned char st[100];
void receive_string(){

	int i=0;
	while(1){
		st[i]=receive_char();
	if(st[i]=='x')break;
	i++;
	}
}
main()
{
	unsigned char ch;
	initLed();
	usart();
	while(1){
		send_string("\nHello,world");
		ch=receive_char();
	if(ch=='a'){
		GPIOC->ODR=0x300;
		send_string("\nHello,boy");
		send_char(ch);
		delay(400000);
	}
	GPIOC->ODR=0x00;

	receive_string();
	send_string("\n Receive");
	send_string(st);
	}
}
*/

