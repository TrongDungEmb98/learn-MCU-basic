//Configure the SYSCLK to 24MHz


#include"stm32f0xx_gpio.h"
#include"stm32f0xx_rcc.h"

void InitPLL_24Mhz(void);
void InitLED(void) ;


main(){
	    InitLED();
  // Sets System clock frequency to 24MHz
		InitPLL_24Mhz();
	//BAT LED TAI PC8, PC9
		if (RCC->CFGR & 0x8)
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


void InitPLL_24Mhz(void)
{
	/* (1)  Test if PLL is used as System clock */
	/* (2)  Select HSI as system clock */
	/* (3)  Wait for HSI switched */
	/* (4)  Disable the PLL */
	/* (5)  Wait until PLLRDY is cleared */
	/* (6)  Set the PLL multiplier to 6 */
	/* (7)  Enable the PLL */
	/* (8)  Wait until PLLRDY is set */
	/* (9)  Select PLL as system clock */
	/* (10) Wait until the PLL is switched on */
	if ((RCC ->CFGR  & RCC_CFGR_SWS ) == RCC_CFGR_SWS_PLL) /* (1) */
	{
	  RCC ->CFGR  &= (uint32_t ) (~RCC_CFGR_SW); /* (2) */
	  while  ((RCC ->CFGR  & RCC_CFGR_SWS ) != RCC_CFGR_SWS_HSI) /* (3) */
	  {
	    /* For robust implementation, add here time-out management */
	  }
	}
	RCC ->CR  &= (uint32_t )(~ RCC_CR_PLLON);/* (4) */
	while ((RCC ->CR  & RCC_CR_PLLRDY) != 0) /* (5) */
	{
	  /* For robust implementation, add here time-out management */
	}
	//GPIOC->ODR =0x100;
	RCC ->CFGR  = RCC->CFGR  & (~RCC_CFGR_PLLMULL)| (RCC_CFGR_PLLMULL6); /* (6) */
	RCC ->CR  |= RCC_CR_PLLON ; /* (7) */
	while ((RCC ->CR  & RCC_CR_PLLRDY) == 0) /* (8) */
	{
	  /* For robust implementation, add here time-out management */
	}
	//GPIOC->ODR =0x100;
	RCC ->CFGR  |= (uint32_t ) (RCC_CFGR_SW_PLL ); /* (9) */
	while  ((RCC ->CFGR  & RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL) /* (10) */
	{
	  /* For robust implementation, add here time-out management */
	}

	GPIOC->ODR=0x200;
}
