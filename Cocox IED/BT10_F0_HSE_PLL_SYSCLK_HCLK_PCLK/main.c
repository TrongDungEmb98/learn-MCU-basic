
//Configure HSE -> PLL -> the SYSCLK to 48MHz --> HCLK (12Mhz) --> PCLK (6Mhz)

#include"stm32f0xx_gpio.h"
#include"stm32f0xx_rcc.h"

void InitPLL_48Mh(void);
void InitLED(void) ;


main(){
	    InitLED();
  // Sets System clock frequency to 48MHz
	    InitPLL_48Mhz();
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


void InitPLL_48Mhz(void)
{
	/* (1)  Test if PLL is used as System clock */
	/* (2)  Select HSI as system clock */
	/* (3)  Wait for HSI switched */

	if ((RCC ->CFGR  & RCC_CFGR_SWS ) == RCC_CFGR_SWS_PLL) /* (1) */
		{
		  RCC ->CFGR  &= (uint32_t ) (~RCC_CFGR_SW); /* (2) */
		  while  ((RCC ->CFGR  & RCC_CFGR_SWS ) != RCC_CFGR_SWS_HSI) /* (3) */
		  {
		    /* For robust implementation, add here time-out management */
		  }
		}

	/* (4)  Disable the PLL */
	/* (5)  Wait until PLLRDY is cleared */
	RCC ->CR  &= (uint32_t )(~ RCC_CR_PLLON);/* (4) */
		while ((RCC ->CR  & RCC_CR_PLLRDY) != 0) /* (5) */
		{
		  /* For robust implementation, add here time-out management */
		}
	/*(6) Set HSE divider for PLL entry (PPLXTPRE) */
		RCC ->CFGR |= RCC_CFGR_PLLXTPRE ; //HSE:2

	/*(7)  Set the PLL source as HSE (PLL_SRC) */
		RCC ->CFGR |= RCC->CFGR  & ((~0x18000) | (RCC_CFGR_PLLSRC));

	/* (8)  Set the PLL multiplier to 12 (4*12=48) */

		RCC ->CFGR  = RCC->CFGR  & (~RCC_CFGR_PLLMULL)| (RCC_CFGR_PLLMULL12); /*(8) */

	 /* (9) Set (AHB prescaler) as SYSCLK divided by 4 (48Mhz/4 = 12Mhz)*/
		RCC ->CFGR  = RCC->CFGR  & (~ RCC_CFGR_HPRE) | (RCC_CFGR_HPRE_DIV4);

	 /*(10) Set (APB prescaler) as HCLK divided by 2 (12Mhz/2 = 6Mhz)*/

		RCC ->CFGR  = RCC->CFGR  & (~ RCC_CFGR_PPRE) | (RCC_CFGR_PPRE_DIV2);

	/* (11)  Enable the PLL */

		RCC ->CR  |= RCC_CR_PLLON ; /* (9) */
	/* (12)  Wait until PLLRDY is set */
		while ((RCC ->CR  & RCC_CR_PLLRDY) == 0) /* (10) */
			{
			  /* For robust implementation, add here time-out management */
			}
	/* (13)  Select PLL as system clock */
		RCC ->CFGR  |= (uint32_t ) (RCC_CFGR_SW_PLL ); /* (11) */
	/* (14) Wait until the PLL is switched on */

		while ((RCC ->CFGR  & RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL) /* (12) */
			{
			  /* For robust implementation, add here time-out management */
			}

}
