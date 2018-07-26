#ifndef _UART_H_
#define _UART_H_

#include "hw_stm32f030r8t6.h"


extern void init_uart(void);
extern char uart_send_byte(const unsigned char c);
extern void uart_send_string(unsigned char* str);

#endif //_UART_H_