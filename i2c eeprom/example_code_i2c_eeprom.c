/* Cấu hình cho i2c stm32f1 */
void stm32f1_init_i2c(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef I2C_InitStructure;
	
	I2C_Cmd(I2C2,ENABLE);
	I2C_DeInit(I2C2);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;//OD
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = i2c_speed ;
	I2C_Init(I2C2, &I2C_InitStructure);
}

/* Chương trình ghi 1byte vào eeprom 24c02 24c04 24c08... */
void write_24CXX (uint16_t Addr, uint16_t data)
{
	I2C_GenerateSTART(I2C2, ENABLE);

	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C2, MEM_DEVICE_WRITE_ADDR, I2C_Direction_Transmitter);

	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C2, Addr);

	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C2, data);

	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTOP(I2C2, ENABLE);
	Delay(5);
}

/* Chương trình đọc 1byte từ 24cxx */
uint8_t read_24CXX(uint16_t Addr)
{
	uint8_t Data = 0;

	I2C_GenerateSTART(I2C2, ENABLE);

	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C2, MEM_DEVICE_WRITE_ADDR, I2C_Direction_Transmitter);

	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C2, Addr);

	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTART(I2C2, ENABLE);

	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C2, MEM_DEVICE_READ_ADDR, I2C_Direction_Receiver);

	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	I2C_GenerateSTOP(I2C2, ENABLE);

	Data = I2C_ReceiveData(I2C2);
	return Data;
}