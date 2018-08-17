#include "hw_stm32f030r8t6.h"

void led_on(unsigned int led, const unsigned int registers);
void led_off(unsigned int led, const unsigned int registers);
volatile unsigned int led_state = 0;
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
}

void EXTI0_IRQHandler(void)
{
  unsigned int temp;
  
  temp = read_reg(EXTI_PR,(1 << 0));
  if(temp == 1){
	  if(led_state == 0){
		  led_on(LD3_PIN,GPIOC_BSRR);
		  led_state = 1;
	  }else{
		  led_off(LD3_PIN,GPIOC_BSRR);
		  led_state = 0;
	  }
  }
  /* Clear pending */
  temp = 1 << 0;
  write_reg(EXTI_PR,temp);
  
  write_reg(NVIC_ICPR,(1<<5));
}

/**************************************************************************************************/
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

/* Init Pin PC9 and PC8 */
void Init_Led(void)
{
	unsigned int tempreg;
/**** 3 follow lines is configuration PC9 that is output pin ****/	

	/* read all bits of GPIOC_MODER register without bits[19:18] */
	tempreg = read_reg(GPIOC_MODER,~(0x03u<<18));
	/* write value 0x10u to bits[19:18] of GPIOC_MODER register */
	tempreg |= (GPIO_OUTPUT_MODE<<18);
	write_reg(GPIOC_MODER,tempreg);
	
/**** 3 follow lines is configuration PC8 that is output pin ****/	

	/* read all bits of GPIOC_MODER register without bits[19:18] */
	tempreg = read_reg(GPIOC_MODER,~(0x03u<<16));
	/* write value 0x10u to bits[19:18] of GPIOC_MODER register */
	tempreg |= (GPIO_OUTPUT_MODE<<16);
	write_reg(GPIOC_MODER,tempreg);	
}

/* Init User Button PA0 */
void Init_Button(void)
{
	unsigned tempreg;
/**** 3 follow lines is configuration PA0 that is input pin ****/	

	/* read all bits of GPIOA_MODER register without bits[1:0] */
	tempreg = read_reg(GPIOA_MODER,~(0x03u<<0));
	/* write value 0x00u to bits[1:0] of GPIOA_MODER register */
	tempreg |= (GPIO_INPUT_MODE<<0);
	write_reg(GPIOA_MODER,tempreg);
}

void inti_interrupt(void)
{
	unsigned int tempreg;
	/* EXTI */
	tempreg = read_reg(EXTI_IMR,~(1<<0));
	tempreg |= (1<<0);
	write_reg(EXTI_IMR,tempreg);
	
	tempreg = read_reg(EXTI_RTSR,~(1<<0));
	tempreg |= (1<<0);
	write_reg(EXTI_RTSR,tempreg);
	
	/* SYSCFG */
	tempreg = read_reg(SYSCFG_EXTICR1,~(0x0F << 0));
	tempreg |= (0x00<<0);
	write_reg(SYSCFG_EXTICR1,tempreg);
	
	/* NVIC */
	/* ID interrput is 5 */
	tempreg = read_reg(NVIC_ISER,~(1 << 5));
	tempreg |= (1 << 5);
	write_reg(NVIC_ISER,tempreg);
	
	/* Enable global interrupt*/
	//asm("cpsie i");
	
	/* Disable global interrupt*/
	//asm("cpsid i");
}

void led_on(unsigned int led, const unsigned int registers)
{
	unsigned int tempreg;
	/* read all bits of GPIOC_BSRR register without bit "led" */
	tempreg = read_reg(registers,~(1u << led));
	/* set bit "led" of GPIOC_BSRR register */
	tempreg |= (1u << led);
	write_reg(registers,tempreg);
	
	/*another way to turn on led*/
	/*
	write_reg(GPIOC_BSRR, 1u << led );
	*/
}

void led_off(unsigned int led, const unsigned int registers)
{
	unsigned int tempreg;
	/* read all bits of GPIOC_BSRR register without bit "led" */
	tempreg = read_reg(registers,~(1u << led));
	/* clear bit "led" of GPIOC_BSRR register */
	tempreg |= (1u << (led + 16u) );
	write_reg(registers,tempreg);
	
	/*another way to turn off led*/
	/*
	write_reg(GPIOC_BSRR,1u << (led+16u) );
	
	*/
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