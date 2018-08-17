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
	init_uart();
	inti_interrupt();
	rx_data = 0;

	uart_send_string("hello world\n\r");
	while(1)
	{
		
	}
}