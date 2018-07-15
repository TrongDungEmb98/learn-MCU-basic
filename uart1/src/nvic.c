#include "stm32lib.j"

/***************************************************************************************/
volatile unsigned int led_state = 0;


/***************************************************************************************/
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
	asm("cpsie i");
	
	/* Disable global interrupt*/
	//asm("cpsid i");
}
