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
	init_uart();
	Init_Pin();
	inti_interrupt();

	uart_send_string("Hello World");
	
	while(1)
	{
		if(rx_data != 0)
		{
			uart_send_byte(rx_data);
		}
		rx_data = 0;
	}
}