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

void main(void)
{	
	SystemInit();
	clock_enable();
	Init_Pin();

	init_systick();
	while(1)
	{
		led_on(LD3_PIN, GPIO_BSRR(PORT_C));
		delay_timer_ms(1000); /* 500 ms*/
		led_off(LD3_PIN, GPIO_BSRR(PORT_C));
		delay_timer_ms(1000); /* 500 ms*/
		
	}
}