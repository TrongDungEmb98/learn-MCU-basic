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
		if(rx_data != 0)
		{
			if(rx_data == 13)
			{
				uart_send_string("13 = \n\r");
			}else{
				//command[num_char] = rx_data;
				uart_send_string(command);
				uart_send_string("\n\r");
				
			}
			rx_data = 0;
		}
	}
}