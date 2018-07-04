#ifndef HW_STM32F030R8T6_H
#define HW_STM32F030R8T6_H

#define write_reg(addr, value)    *((unsigned long int *)(addr)) = value
#define read_reg(addr, mask)      *((unsigned long int *)(addr)) & (mask)

/* GPIO */
#define BASE_ADDR_GPIO_A	0x48000000u
#define BASE_ADDR_GPIO_B	0x48000400u
#define BASE_ADDR_GPIO_C	0x48000800u
#define BASE_ADDR_GPIO_D	0x48000C00u

#define GPIOC_MODER		(BASE_ADDR_GPIO_C + 0x00u)
#define GPIOC_OTYPER	(BASE_ADDR_GPIO_C + 0x04u)
#define GPIOC_OSPEEDR	(BASE_ADDR_GPIO_C + 0x08u)
#define GPIOC_PUPDR		(BASE_ADDR_GPIO_C + 0x0Cu)
#define GPIOC_ODR		(BASE_ADDR_GPIO_C + 0x14u)
#define GPIOC_BSRR		(BASE_ADDR_GPIO_C + 0x18u)
#define GPIOC_LCKR		(BASE_ADDR_GPIO_C + 0x1Cu)
#define GPIOC_AFRL		(BASE_ADDR_GPIO_C + 0x20u)
#define GPIOC_AFRH		(BASE_ADDR_GPIO_C + 0x24u)
#define GPIOC_BRR		(BASE_ADDR_GPIO_C + 0x28u)



#define GPIO_INPUT_MODE			0x00u
#define GPIO_OUTPUT_MODE		0x01u
#define GPIO_ALTERNATE_MODE		0x02u
#define GPIO_ANLALOG_MODE		0x03u

/* RCC - clocks */
#define BASE_ADDR_RCC			0x40021000u
#define RCC_AHBENR				(BASE_ADDR_RCC + 0x14u)


/* Led: LD3 - PC9 */
#define LD3_PIN					9

#endif  /* HW_STM32F030R8T6_H */