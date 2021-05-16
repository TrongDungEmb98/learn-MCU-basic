#include "stm32_i2c.h"

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_rcc.h"

/****************************** PRIVATE API *******************************/
static uint8_t ic2_start(void)
{
	if (I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY) == SET) {
        os_trace("i2c2 is busy\n", __FILE__, __LINE__);
        return 1; /* busy */
    }

    /* Send start */
    I2C_GenerateSTART(I2C2, ENABLE);

    /* wait SB bit in SR1 is set - check EV5 */
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
    return 0;
}

static void ic2_stop(void)
{
    /* Send STOP Condition */
    I2C_GenerateSTOP(I2C2, ENABLE);
    /* Make sure that the STOP bit is cleared by Hardware before CR1 write access */
    while (I2C2->CR1 & (1 << 9));
}

static void send_address_for_writing(uint8_t address)
{
    os_trace("slave address: %x - %x\n", address, address << 1);

    I2C_Send7bitAddress(I2C2, address << 1, I2C_Direction_Transmitter);

    /* wait ADDR bit in SR1 is set - check EV6 */
    while (I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR);
}

static void send_address_for_reading(uint8_t address)
{
    I2C_Send7bitAddress(I2C2, address << 1, I2C_Direction_Receiver);

    /* wait ADDR bit in SR1 is set - check EV6 */
    while (I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) == ERROR);
}

static void i2c_write(uint8_t data)
{
    /* send data */
    I2C_SendData(I2C2, data);

    /* Wait until BTF is set before programming the STOP - EV8 */
    while (I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR);
}

static uint8_t i2c_read_byte(void)
{
    /* Wait until BTF is set before programming the STOP - EV7*/
    while (I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED) == ERROR);

    return I2C_ReceiveData(I2C2);
}

/****************************** PUBLIC API *******************************/
void i2c_init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef gpio_mux;
    gpio_mux.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    gpio_mux.GPIO_Mode = GPIO_Mode_AF;
    gpio_mux.GPIO_PuPd = GPIO_PuPd_NOPULL; /* open drain */
    GPIO_Init(GPIOB, &gpio_mux);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_I2C2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_I2C2);

    I2C_InitTypeDef i2c2;
    i2c2.I2C_ClockSpeed = 100000;
    i2c2.I2C_Mode = I2C_Mode_I2C;
    i2c2.I2C_DutyCycle = I2C_DutyCycle_2; /* but not used */
    i2c2.I2C_OwnAddress1 = 0x00;
    i2c2.I2C_Ack = I2C_Ack_Disable;
    i2c2.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C2, &i2c2);
    I2C_Cmd(I2C2, ENABLE);
}

uint32_t i2c_send_byte(uint8_t address, uint8_t data)
{
    /* disable ack */
    I2C_AcknowledgeConfig(I2C2, DISABLE);

    /* send START condition */
    if (ic2_start())
        return 1; /* i2c bus is busy */

    /* send slave's address for write */
    send_address_for_writing(address);
    
    /* send data */
    i2c_write(data);

    /* Send STOP Condition */
    ic2_stop();

    return 0;
}

uint32_t i2c_send_data(uint8_t address, uint8_t *data, uint32_t len)
{
    os_trace("i2c_send_data:\n");
    /* disable ack */
    I2C_AcknowledgeConfig(I2C2, DISABLE);

    /* send START condition */
    if (ic2_start())
        return 0; /* i2c bus is busy */

    /* send slave's address for write */
    send_address_for_writing(address);

    /* send data */
    while(len--) {
        os_trace("%02x ", *data);
        i2c_write(*data);
        data++;
    }
    os_trace("\n");

    /* Send STOP Condition */
    ic2_stop();

    return len;
}

uint32_t i2c_read(uint32_t slaveAddr, uint8_t dataAddr, uint8_t *data, uint32_t len)
{
    /* enable ack */
    I2C_AcknowledgeConfig(I2C2, ENABLE);

    /* send START condition */
    if (ic2_start())
        return 0; /* i2c bus is busy */

    /* send slave's address for write */
    send_address_for_writing(slaveAddr);

    /* send register address need read */
    i2c_write(dataAddr);

    ic2_start(); /* repeat start */
    /* send slave's address for read */
    send_address_for_reading(slaveAddr);

    /* read data */
    uint32_t i;
    for (i = 0; i <len; i++)
        data[i] = i2c_read_byte();

    /* Send STOP Condition */
    ic2_stop();

    return i;
}
