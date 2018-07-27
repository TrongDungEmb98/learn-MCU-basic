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
	uart_send_string("hello world");
	while(1)
	{
		delay(0x5F);
		uart_send_byte(0x55);
	}
}