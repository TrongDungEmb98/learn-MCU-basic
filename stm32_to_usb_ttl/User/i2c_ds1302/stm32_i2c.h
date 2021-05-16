#ifndef _STM32_I2C_H_
#define _STM32_I2C_H_

#include "stm32f4xx.h"

#include "Debug.h"

#define I2C2_SCL_PIN    GPIO_PIN_10     /* PB10 */
#define I2C2_SDA_PIN    GPIO_PIN_11     /* PB11 */
#define I2C2_GPIO       GPIOB

void i2c_init(void);
uint32_t i2c_send_byte(uint8_t address, uint8_t data);
uint32_t i2c_send_data(uint8_t address, uint8_t *data, uint32_t len);
uint32_t i2c_read(uint32_t slaveAddr, uint8_t dataAddr, uint8_t *data, uint32_t len);

#endif /* _STM32_I2C_H_ */
