#include "hw_stm32f030r8t6.h"

void Reserved_IRQHandler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void NMI_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void HardFault_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void SVC_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void PendSV_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void SysTick_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}/**************************************************************************************************/
void delay(unsigned int timeout)
{
    unsigned int t1, t2;
    for (t1 = 0; t1 < timeout; t1++)
    {
        for (t2 = 0; t2 < 0xFFF; t2++)
        {
          asm(" nop");
        }
    }
}
/*Enable Clock*/
void clock_enable(void)
{
	unsigned int tempreg;
	
	/*enable clock GPIO C*/
	tempreg = read_reg(RCC_AHBENR,~(1<<19));
	tempreg |=	(1<<19);
	write_reg(RCC_AHBENR,tempreg);
}

/* Init Pin PC9*/
void Init_Pin(void)
{
	unsigned int tempreg;
/**** 3 follow lines is configuration PC9 that is output pin ****/	

	/* read all bits of GPIOC_MODER register without bits[19:18] */
	tempreg = read_reg(GPIOC_MODER,~(0x03u<<18));
	/* write value 0x10 to bits[19:18] of GPIOC_MODER register */
	tempreg |= (GPIO_OUTPUT_MODE<<18);
	write_reg(GPIOC_MODER,tempreg);
}

void led_on(unsigned int led)
{
	unsigned int tempreg;
	/* read all bits of GPIOC_BSRR register without bit "led" */
	tempreg = read_reg(GPIOC_BSRR,~(1u << led));
	/* set bit "led" of GPIOC_BSRR register */
	tempreg |= (1u << led);
	write_reg(GPIOC_BSRR,tempreg);
	
	/*another way to turn on led*/
	/*
	write_reg(GPIOC_BSRR, 1u << led );
	*/
}

void led_off(unsigned int led)
{
	unsigned int tempreg;
	/* read all bits of GPIOC_BSRR register without bit "led" */
	tempreg = read_reg(GPIOC_BSRR,~(1u << led));
	/* clear bit "led" of GPIOC_BSRR register */
	tempreg |= (1u << (led + 16u) );
	write_reg(GPIOC_BSRR,tempreg);
	
	/*another way to turn off led*/
	/*
	write_reg(GPIOC_BSRR,1u << (led+16u) );
	
	*/
}

void main(void)
{
	clock_enable();
	Init_Pin();
	while(1)
	{
		led_on(LD3_PIN);
		delay(0xff);
		led_off(LD3_PIN);
		delay(0xff);
	}
}