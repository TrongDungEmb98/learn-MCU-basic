//Configure HSE (8MHz) to the SYSCLK

#include"stm32f0xx_gpio.h"
#include"stm32f0xx_rcc.h"

void InitHSE_8Mhz(void);
void InitLED(void) ;

main(){
	    InitLED();
  // Sets System clock frequency to 8MHz
	    InitHSE_8Mhz();
	//BAT LED TAI PC8, PC9
		if (RCC->CFGR & 0x4) // RCC_CFGR_SWS = 01 ~ HSE la SYSCLK
			GPIOC->ODR=0x300;
        while(1);

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


void InitHSE_8Mhz(void)
{
	// (if HSE is not SYSCLK)
	if ((RCC ->CFGR  & RCC_CFGR_SWS ) != RCC_CFGR_SWS_HSE) /* (1) */
	{
			GPIOC->ODR=0x100;  //Bat LED tai PC8


			//set CSSON, HSEBYP and RCC_CR_HSEON bits   (2)
			RCC ->CR  |=(uint32_t) RCC_CR_CSSON | RCC_CR_HSEBYP  | RCC_CR_HSEON ;

			//Waiting until HSERDY bit as 1 ~ HSE ready
			while ((RCC ->CR  & RCC_CR_HSERDY) == 0) /* (3) */
			{
			  /* For robust implementation, add here time-out management */
			}
			GPIOC->ODR=0x200; // Bat LED tai PC 9


			//Switch HSE as SYSCLK; /* (4) */
			RCC->CFGR  = ((RCC ->CFGR  & (~RCC_CFGR_SW)) | RCC_CFGR_SW_0);

			// Waiting until HSE as SYSCLK (5)
			while  ((RCC ->CFGR  & RCC_CFGR_SWS ) != RCC_CFGR_SWS_HSE) /* (5) */
				{
				  /* For robust implementation, add here time-out management */
				}

	}





}
