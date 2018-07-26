#include "stm32lib.h"


/**
  * @brief  Setup the microcontroller system.
  *         Initialize the default HSI clock source, vector table location and the PLL configuration is reset.
  * @param
  *         hsi_prediv: hệ số chia clock từ HSI RC đưa vào PLL Source Mux
  *         pullmux: hệ số chia clock trong khối PLL
  *         pllsrc: hệ số chia clock trong khối PLL
  *         ahb_div: hệ số chia clock cho AHB prescaler
  *         system_source: lựa chọn source clock cho system thông qua System Clock Mux
  *         apb1_div: hệ số chia clock cho APB1 prescaler
  * @retval None
  */
void SystemInit(void)
{
	unsigned int temp_reg;
  /* Reset the RCC clock configuration to the default reset state ------------*/
  /* Set HSION bit */
	//RCC->CR |= (uint32_t)0x00000001U;
	temp_reg = read_reg(RCC_CR, ~0x01u);
	temp_reg |= (1 << 0);
	write_reg(RCC_CR, temp_reg);
	
	/* Reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE, MCOSEL[2:0], MCOPRE[2:0] and PLLNODIV bits */
	//RCC->CFGR &= (uint32_t)0x08FFB80CU;
	temp_reg = read_reg(RCC_CFGR, 0x08FFB80Cu);
	write_reg(RCC_CFGR, temp_reg);
	
	/* Reset HSEON, CSSON and PLLON bits */
	//RCC->CR &= (uint32_t)0xFEF6FFFFU;
	temp_reg = read_reg(RCC_CR, 0xFEF6FFFFU);
	write_reg(RCC_CR, temp_reg);
	
	/* Reset HSEBYP bit */
	//RCC->CR &= (uint32_t)0xFFFBFFFFU;
	temp_reg = read_reg(RCC_CR, 0xFFFBFFFFU);
	write_reg(RCC_CR, temp_reg);
	
	/* Reset PLLSRC, PLLXTPRE and PLLMUL[3:0] bits */
	//RCC->CFGR &= (uint32_t)0xFFC0FFFFU;
	temp_reg = read_reg(RCC_CFGR,0xFFC0FFFFU);
	write_reg(RCC_CFGR, temp_reg);
	
	/* Reset PREDIV[3:0] bits */
	//RCC->CFGR2 &= (uint32_t)0xFFFFFFF0U;
	temp_reg = read_reg(RCC_CFGR2, 0xFFFFFFF0U);
	write_reg(RCC_CFGR2, temp_reg);

	/* Reset USART1SW[1:0], I2C1SW and ADCSW bits */
	//RCC->CFGR3 &= (uint32_t)0xFFFFFEECU;
	temp_reg = read_reg(RCC_CFGR3, 0xFFFFFEECU);
	write_reg(RCC_CFGR3, temp_reg);
	
	/* Reset HSI14 bit */
	//RCC->CR2 &= (uint32_t)0xFFFFFFFEU;
	temp_reg = read_reg(RCC_CR2, 0xFFFFFFFEU);
	write_reg(RCC_CR2, temp_reg);
	
	/* Disable all interrupts */
	//RCC->CIR = 0x00000000U;
	temp_reg = read_reg(RCC_CIR, 0x00000000U);
	write_reg(RCC_CIR, temp_reg);
}

/*Enable Clock*/
void clock_enable(void)
{
	unsigned int tempreg;
	
	/*enable clock GPIO C */
	tempreg = read_reg(RCC_AHBENR,~(1u<<19));
	tempreg |=	(1u<<19);
	write_reg(RCC_AHBENR,tempreg);
	
	/* enable clock GPIO A */
	tempreg = read_reg(RCC_AHBENR,~(1u<<17));
	tempreg |=	(1u<<17);
	write_reg(RCC_AHBENR,tempreg);
	
	/* usart1 */
    tempreg = read_reg(RCC_APB2ENR, ~(1 << 14));
    tempreg = tempreg | (1 << 14);
    write_reg(RCC_APB2ENR, tempreg);
	
}