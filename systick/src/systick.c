#include "stm32lib.h"

void init_systick(void)
{
	unsigned int temp_reg;
	/* Disable systick */
	write_reg(SYST_CSR, 0x00u);
	
	/* Source Clock */
	temp_reg = read_reg(SYST_CSR, ~(1 << 2));
	temp_reg |= (1 << 2);
	write_reg(SYST_CSR, temp_reg);
	
	/* Clear Current value */
	write_reg(SYST_CVR, 0x00u );
}
void start_timer(unsigned int value)
{
	unsigned int temp_reg;
	
	/* set reload value and current value*/
	write_reg(SYST_RVR, value );
	write_reg(SYST_CVR, 0x00u );
	
	/* Start timer */
	temp_reg = read_reg(SYST_CSR, ~(1 << 0));
	temp_reg |= 1 << 0;
	write_reg(SYST_CSR, temp_reg);
}
unsigned int get_state_timer(void)
{
	unsigned int tempreg;

    /* COUNTFLAG */
    tempreg = read_reg(SYST_CSR, 1 << 16);
    tempreg = tempreg >> 16;

    return tempreg;
}
void delay_timer_ms(unsigned int value)
{
	while(value--)
	{
		start_timer(0xBB7F);  /* 1ms */
		while(get_state_timer() == 0);
	}
}