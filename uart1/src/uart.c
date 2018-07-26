#include "stm32lib.h"


void init_uart(void)
{
	unsigned int temp_reg;

	write_reg(USART_CR1,0x0u);
	/* UE = 0 */
	temp_reg = read_reg(USART_CR1,~(1u << 0));
	temp_reg |= (0 << 0);
	
	/* 1 bit start, 8 bit data, n bit stop */
	temp_reg = read_reg(USART_CR1,~((1u << 28) | (1u << 12)));
	temp_reg |= ((0 << 28) | (0<<12));
	
	/* None parity bit */
	temp_reg = read_reg(USART_CR1,~(1u << 10));
	temp_reg |= (0 << 10);
	
	/* 1 bit stop */
	temp_reg = read_reg(USART_CR1,~(0x03u << 12));
	temp_reg |= (0 << 12);
	
	/* Oversampling by 16*/
	temp_reg = read_reg(USART_CR1,~(0x1u << 15));
	temp_reg |= (0 << 15);
	
	/* set Baudrate = 9600, Fck = 8MHz */
	write_reg(USART_BRR, 0x341u);
		
	/* enable UART UE = 1 */
	temp_reg = read_reg(USART_CR1,~(1u << 0));
	temp_reg |= (1 << 0);
	write_reg(USART_CR1, temp_reg);
	
	/* Enable TE */
	temp_reg = read_reg(USART_CR1,~(0x1u << 3));
	temp_reg |= (1u << 3);
	write_reg(USART_CR1, temp_reg);
	
	/* Enable RE */
	temp_reg = read_reg(USART_CR1,~(0x1u << 2));
	temp_reg |= (1u << 2);
	write_reg(USART_CR1, temp_reg);
	
}

char uart_send_byte(unsigned char c)
{
	char state = 0;
	
	// kiem tra TX buffer đã sẵn sàng nhận data mới chưa
	unsigned int temp_reg = read_reg(USART_ISR,(0x1 << 7));
	
	if(0 != temp_reg)
	{
		write_reg(USART_TDR,(unsigned int) c);
	}else{
		state = -1;
	}
	return state;
}
void uart_send_string(unsigned char* str)
{
// Neu truyen thanh cong byte truoc do thi truyen byte tiep theo, neu khong thi truyen lai.
	while(*str)
	{
		if( uart_send_byte(*str) == 0 )
		{
			str ++;
		}	
	}
}

















