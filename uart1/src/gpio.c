#include "stm32lib.h"


/* Init Pin PC9 and PC8 */
void Init_Led(void)
{
	unsigned int tempreg;
/**** 3 follow lines is configuration PC9 that is output pin ****/	

	/* read all bits of GPIOC_MODER register without bits[19:18] */
	tempreg = read_reg(GPIOC_MODER,~(0x03u<<18));
	/* write value 0x10u to bits[19:18] of GPIOC_MODER register */
	tempreg |= (GPIO_OUTPUT_MODE<<18);
	write_reg(GPIOC_MODER,tempreg);
	
/**** 3 follow lines is configuration PC8 that is output pin ****/	

	/* read all bits of GPIOC_MODER register without bits[19:18] */
	tempreg = read_reg(GPIOC_MODER,~(0x03u<<16));
	/* write value 0x10u to bits[19:18] of GPIOC_MODER register */
	tempreg |= (GPIO_OUTPUT_MODE<<16);
	write_reg(GPIOC_MODER,tempreg);	
}

/* Init User Button PA0 */
void Init_Button(void)
{
	unsigned tempreg;
/**** 3 follow lines is configuration PA0 that is input pin ****/	

	/* read all bits of GPIOA_MODER register without bits[1:0] */
	tempreg = read_reg(GPIOA_MODER,~(0x03u<<0));
	/* write value 0x00u to bits[1:0] of GPIOA_MODER register */
	tempreg |= (GPIO_INPUT_MODE<<0);
	write_reg(GPIOA_MODER,tempreg);
}


void led_on(unsigned int led, const unsigned int registers)
{
	unsigned int tempreg;
	/* read all bits of GPIOC_BSRR register without bit "led" */
	tempreg = read_reg(registers,~(1u << led));
	/* set bit "led" of GPIOC_BSRR register */
	tempreg |= (1u << led);
	write_reg(registers,tempreg);
	
	/*another way to turn on led*/
	/*
	write_reg(GPIOC_BSRR, 1u << led );
	*/
}

void led_off(unsigned int led, const unsigned int registers)
{
	unsigned int tempreg;
	/* read all bits of GPIOC_BSRR register without bit "led" */
	tempreg = read_reg(registers,~(1u << led));
	/* clear bit "led" of GPIOC_BSRR register */
	tempreg |= (1u << (led + 16u) );
	write_reg(registers,tempreg);
	
	/*another way to turn off led*/
	/*
	write_reg(GPIOC_BSRR,1u << (led+16u) );
	
	*/
}
