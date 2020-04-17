#ifndef __L1_GPIO_H
#define __L1_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx.h"

 typedef enum
 {
   GPIO_Mode_IN   = 0x00, /*!< GPIO Input Mode */
   GPIO_Mode_OUT  = 0x01, /*!< GPIO Output Mode */
   GPIO_Mode_AF   = 0x02, /*!< GPIO Alternate function Mode */

 }GPIOMode_TypeDef;

 typedef enum
 { GPIO_OType_PP = 0x00,
   GPIO_OType_OD = 0x01
 }GPIOOType_TypeDef;


 typedef enum
 {
   GPIO_Speed_400KHz = 0x00, /*!< Very Low Speed */
   GPIO_Speed_2MHz   = 0x01, /*!< Low Speed */
   GPIO_Speed_10MHz  = 0x02, /*!< Medium Speed */
   GPIO_Speed_40MHz  = 0x03  /*!< High Speed */
 }GPIOSpeed_TypeDef;


 typedef enum
 { GPIO_PuPd_NOPULL = 0x00,
   GPIO_PuPd_UP     = 0x01,
   GPIO_PuPd_DOWN   = 0x02
 }GPIOPuPd_TypeDef;


typedef struct
{
  uint32_t GPIO_Pin;
  GPIOMode_TypeDef GPIO_Mode;
  GPIOSpeed_TypeDef GPIO_Speed;
  GPIOOType_TypeDef GPIO_OType;
  GPIOPuPd_TypeDef GPIO_PuPd;
}GPIO_InitTypeDef;



#define GPIO_Pin_8                 ((uint16_t)0x0100)  /*!< Pin 8 selected */
#define GPIO_Pin_9                 ((uint16_t)0x0200)  /*!< Pin 9 selected */

#ifdef __cplusplus
}
#endif

#endif
