#include"stm32l1xx.h"
#include"stm32l1xx_rcc.h"

typedef struct
{
  __IO uint32_t MODER;        /*!< GPIO port mode register,                     Address offset: 0x00      */
  __IO uint16_t OTYPER;       /*!< GPIO port output type register,              Address offset: 0x04      */
  uint16_t RESERVED0;         /*!< Reserved,                                    0x06                      */
  __IO uint32_t OSPEEDR;      /*!< GPIO port output speed register,             Address offset: 0x08      */
  __IO uint32_t PUPDR;        /*!< GPIO port pull-up/pull-down register,        Address offset: 0x0C      */
  __IO uint16_t IDR;          /*!< GPIO port input data register,               Address offset: 0x10      */
  uint16_t RESERVED1;         /*!< Reserved,                                    0x12                      */
  __IO uint16_t ODR;          /*!< GPIO port output data register,              Address offset: 0x14      */
  uint16_t RESERVED2;         /*!< Reserved,                                    0x16                      */
  __IO uint16_t BSRRL;        /*!< GPIO port bit set/reset low registerBSRR,    Address offset: 0x18      */
  __IO uint16_t BSRRH;        /*!< GPIO port bit set/reset high registerBSRR,   Address offset: 0x1A      */
  __IO uint32_t LCKR;         /*!< GPIO port configuration lock register,       Address offset: 0x1C      */
  __IO uint32_t AFR[2];       /*!< GPIO alternate function low register,        Address offset: 0x20-0x24 */
  __IO uint16_t BRR;          /*!< GPIO bit reset register,                     Address offset: 0x28      */
  uint16_t RESERVED3;         /*!< Reserved,                                    0x2A                      */
} GPIO_TypeDef_C;


#define PERIPH_BASE           ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region */

#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)

#define GPIOC_BASE            (AHBPERIPH_BASE + 0x0800)

#define GPIOC_1               ((GPIO_TypeDef_C *) GPIOC_BASE)


int main(void)
{
	//Cap xung nhip cong C
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC;

	GPIOC_1->MODER=0x50000;
	GPIOC_1->OTYPER=0x0;
	GPIOC_1->PUPDR=0x0;
	GPIOC_1->OSPEEDR=0xF0000;


    while(1)
    {
    	GPIOC_1->BSRRL=0x300; //set bit PC8, PC9
    	delay();  //tu viet ham delay
    	GPIOC_1->BSRRH=0x300;//reset bit PC8, Pc9
    	delay();

    }
}
