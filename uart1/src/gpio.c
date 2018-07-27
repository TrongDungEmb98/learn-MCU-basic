#include "stm32lib.h"

/* Init Pin PC9 and PC8 */
void Init_Pin(void)
{
	unsigned int tempreg;
/**** 3 follow lines is configuration PC9 that is output pin ****/	

	/* read all bits of GPIOC_MODER register without bits[19:18] */
	tempreg = read_reg(GPIO_MODER(PORT_C),~(0x03u<<18));
	/* write value 0x10u to bits[19:18] of GPIOC_MODER register */
	tempreg |= (GPIO_OUTPUT_MODE<<18);
	write_reg(GPIO_MODER(PORT_C),tempreg);
	
/**** 3 follow lines is configuration PC8 that is output pin ****/	

	/* read all bits of GPIOC_MODER register without bits[19:18] */
	tempreg = read_reg(GPIO_MODER(PORT_C),~(0x03u<<16));
	/* write value 0x10u to bits[19:18] of GPIOC_MODER register */
	tempreg |= (GPIO_OUTPUT_MODE<<16);
	write_reg(GPIO_MODER(PORT_C),tempreg);	
	
/**** 3 follow lines is configuration PA0 that is input pin ****/	

	/* read all bits of GPIOA_MODER register without bits[1:0] */
	tempreg = read_reg(GPIO_MODER(PORT_A),~(0x03u<<0));
	/* write value 0x00u to bits[1:0] of GPIOA_MODER register */
	tempreg |= (GPIO_INPUT_MODE<<0);
	write_reg(GPIO_MODER(PORT_A),tempreg);

/*** Config PA9 PA10 is Alternate function to use UART1 ***/
	/* PA10 - Rx */
    tempreg = read_reg(GPIO_MODER(PORT_A), ~(0x03 << 20));
    tempreg |= (GPIO_ALTERNATE_MODE << 20);
    write_reg(GPIO_MODER(PORT_A), tempreg);

    tempreg = read_reg(GPIO_AFRH(PORT_A), ~(0xF << 8));
    tempreg |= (AF1 << 8);
    write_reg(GPIO_AFRH(PORT_A), tempreg);

    /* PA9 - Tx */
    tempreg = read_reg(GPIO_MODER(PORT_A), ~(0x03 << 18));
    tempreg |= (GPIO_ALTERNATE_MODE << 18);
    write_reg(GPIO_MODER(PORT_A), tempreg);

    tempreg = read_reg(GPIO_AFRH(PORT_A), ~(0xF << 4));
    tempreg |= (AF1 << 4);
    write_reg(GPIO_AFRH(PORT_A), tempreg);
}


void led_on(unsigned int led, const unsigned int registers)
{
	write_reg(registers, 1u << led );
}

void led_off(unsigned int led, const unsigned int registers)
{
	write_reg(registers,1u << (led+16u) );
}
