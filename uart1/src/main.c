#include "stm32lib.h"

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
	
	/*enable clock GPIO C */
	tempreg = read_reg(RCC_AHBENR,~(1u<<19));
	tempreg |=	(1u<<19);
	write_reg(RCC_AHBENR,tempreg);
	
	/* enable clock GPIO A */
	tempreg = read_reg(RCC_AHBENR,~(1u<<17));
	tempreg |=	(1u<<17);
	write_reg(RCC_AHBENR,tempreg);
	
}

void main(void)
{
	unsigned int tempreg;
	unsigned short int state_led = 0;
	
	clock_enable();
	Init_Led();
	Init_Button();
	inti_interrupt();
	while(1)
	{
		led_on(LD4_PIN,GPIOC_BSRR);
		delay(0xff);
		led_off(LD4_PIN,GPIOC_BSRR);
		delay(0xff);
	}
}