#ifndef HW_STM32F030R8T6_H
#define HW_STM32F030R8T6_H

#define write_reg(addr, value)    *((unsigned long int *)(addr)) = value
#define read_reg(addr, mask)      *((unsigned long int *)(addr)) & (mask)

typedef unsigned int            u32_t;
typedef unsigned short          u16_t;
typedef unsigned char           u8_t;


/*================== RCC - clocks ==============================*/
#define BASE_ADDR_RCC			0x40021000u

#define RCC_CR                  (BASE_ADDR_RCC + 0x00)
#define RCC_CFGR                (BASE_ADDR_RCC + 0x04)
#define RCC_CIR                 (BASE_ADDR_RCC + 0x08)
#define RCC_AHBENR              (BASE_ADDR_RCC + 0x14)
#define RCC_APB2ENR             (BASE_ADDR_RCC + 0x18)
#define RCC_CFGR2               (BASE_ADDR_RCC + 0x2C)
#define RCC_CFGR3               (BASE_ADDR_RCC + 0x30)
#define RCC_CR2                 (BASE_ADDR_RCC + 0x34)

#define PREDIV_1                0u
#define PREDIV_2                1u
#define PREDIV_3                2u
#define PREDIV_4                3u
#define PREDIV_5                4u
#define PREDIV_6                5u
#define PREDIV_7                6u
#define PREDIV_8                7u
#define PREDIV_9                8u
#define PREDIV_10               9u
#define PREDIV_11               10u
#define PREDIV_12               11u
#define PREDIV_13               12u
#define PREDIV_14               13u
#define PREDIV_15               14u
#define PREDIV_16               15u

#define PLL_MUL_2               0u
#define PLL_MUL_3               1u
#define PLL_MUL_12              10u

#define PLL_SCR_HSI             0u

#define SYSCLKSOURCE_PLLCLK     2u

#define APB1_HCLK_1             0u
#define APB1_HCLK_2             4u
#define APB1_HCLK_4             5u
#define APB1_HCLK_8             6u
#define APB1_HCLK_16            7u

/*======================== GPIO =================================*/
#define BASE_ADDR_GPIO					0x48000000u

/*          address register = base address gpio port + offset					   */
/*    base address gpio port = [ base address gpio port A + (400 * port) ]         */
#define GPIO_MODER(port)				(BASE_ADDR_GPIO + (0x400u * (port)) + 0x00u)
#define GPIO_OTYPER(port)				(BASE_ADDR_GPIO + (0x400u * (port)) +0x04u)
#define GPIO_OSPEEDR(port)				(BASE_ADDR_GPIO + (0x400u * (port)) +0x08u)
#define GPIO_PUPDR(port)				(BASE_ADDR_GPIO + (0x400u * (port)) +0x0Cu)
#define GPIO_IDR(port)					(BASE_ADDR_GPIO + (0x400u * (port)) +0x10u)
#define GPIO_ODR(port)					(BASE_ADDR_GPIO + (0x400u * (port)) +0x14u)
#define GPIO_BSRR(port)					(BASE_ADDR_GPIO + (0x400u * (port)) +0x18u)
#define GPIO_LCKR(port)					(BASE_ADDR_GPIO + (0x400u * (port)) +0x1Cu)
#define GPIO_AFRL(port)					(BASE_ADDR_GPIO + (0x400u * (port)) +0x20u)
#define GPIO_AFRH(port)					(BASE_ADDR_GPIO + (0x400u * (port)) +0x24u)
#define GPIO_BRR(port)					(BASE_ADDR_GPIO + (0x400u * (port)) +0x28u)

/* definition port id */
#define PORT_A                  0u
#define PORT_B                  1u
#define PORT_C                  2u
#define PORT_D                  3u
#define PORT_E                  4u
#define PORT_F                  5u


/* GPIO MODEs */
#define GPIO_INPUT_MODE			0x00u
#define GPIO_OUTPUT_MODE		0x01u
#define GPIO_ALTERNATE_MODE		0x02u
#define GPIO_ANLALOG_MODE		0x03u

/* alternate */
#define AF0                     0x0
#define AF1                     0x1
#define AF2                     0x2
#define AF3                     0x3
#define AF4                     0x4
#define AF5                     0x5
#define AF6                     0x6
#define AF7                     0x7

/*======================= EXTI =================================*/
#define BASE_ADRR_EXTI			0x40010400u
#define EXTI_IMR				(BASE_ADRR_EXTI + 0x00u)
#define EXTI_RTSR				(BASE_ADRR_EXTI + 0x08u)
#define EXTI_PR					(BASE_ADRR_EXTI + 0x14u)

/*===================== SYSCFG ===============================*/
#define BASE_ADDR_SYSCFG		0x40010000u
#define SYSCFG_EXTICR1			(BASE_ADDR_SYSCFG + 0x08u)

/*====================== NVIC =================================*/
#define NVIC_ISER				0xE000E100u
#define NVIC_ICER				0xE000E180u
#define NVIC_ISPR				0xE000E200u
#define NVIC_ICPR				0xE000E280u
#define NVIC_ICPR5				0xE000E404u			// IRQ5

/*===================== UART1 ===============================*/
#define BASE_ADDR_UART1			0x40013800u
#define USART_CR1				(BASE_ADDR_UART1 + 0x00u)
#define USART_CR2				(BASE_ADDR_UART1 + 0x04u)
#define USART_CR3				(BASE_ADDR_UART1 + 0x08u)
#define USART_BRR				(BASE_ADDR_UART1 + 0x0Cu)
#define USART_RTOR				(BASE_ADDR_UART1 + 0x14u)
#define USART_RQR				(BASE_ADDR_UART1 + 0x18u)
#define USART_ISR				(BASE_ADDR_UART1 + 0x1Cu)
#define USART_ICR				(BASE_ADDR_UART1 + 0x20u)
#define USART_RDR				(BASE_ADDR_UART1 + 0x24u)
#define USART_TDR				(BASE_ADDR_UART1 + 0x28u)


/* Led: LD3 - PC9       */
#define LD3_PIN					9
/* Led: LD4 - PC8	  */
#define LD4_PIN					8
/* User Button - PA0 */
#define User_Button				0


#endif  /* HW_STM32F030R8T6_H */