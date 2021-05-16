#include "lcd_i2c.h"

#include "stm32_i2c.h"

#define SLAVE_ADDRESS 0x27 /* 0x27 << 1 */

#define READ_MODE 0x01
#define WRITE_MODE 0x00

extern void delay_ms(uint32_t time_ms);

static void lcd_send_cmd(uint8_t cmd)
{
    char data_u, data_l;
    uint8_t data_t[4];

    data_u = (cmd & 0xf0);
    data_l = ((cmd << 4) & 0xf0);

    data_t[0] = data_u | 0x04;  // en=1, rs=0
    data_t[1] = data_u;  // en=0, rs=0
    data_t[2] = data_l | 0x04;  // en=1, rs=0
    data_t[3] = data_l | 0x08;  // en=0, rs=0

    os_trace("lcd_send_cmd: %x-%x-%x-%x\n",
            data_t[0], data_t[1], data_t[2], data_t[3]);
    i2c_send_data(SLAVE_ADDRESS, data_t, 4);
}

void lcd_send_data(char data)
{
    char data_u, data_l;
    uint8_t data_t[4];

    data_u = (data & 0xf0);
    data_l = ((data << 4) & 0xf0);

    data_t[0] = data_u | 0x0D;  // en=1, rs=1
    data_t[1] = data_u | 0x09;  // en=0, rs=1
    data_t[2] = data_l | 0x0D;  // en=1, rs=1
    data_t[3] = data_l | 0x09;  // en=0, rs=1

    os_trace("lcd_send_data: %x-%x-%x-%x\n", data_t[0], data_t[1], data_t[2],
             data_t[3]);

    i2c_send_data(SLAVE_ADDRESS, data_t, 4);
}

void lcd_send_string(char *str)
{
    while (*str)
        lcd_send_data(*str++);
}

void lcd_clear_display(void)
{
    lcd_send_cmd(0x01);  // clear display
}

void lcd_goto_XY(int row, int col)
{
    uint8_t pos_Addr;
    if (row == 1) {
        pos_Addr = 0x80 + row - 1 + col;
    } else {
        pos_Addr = 0x80 | (0x40 + col);
    }
    lcd_send_cmd(pos_Addr);
}

void lcd_i2c_init(void)
{
    i2c_init();

	lcd_send_cmd (0x33); /* set 4-bits interface */
	lcd_send_cmd (0x32);
	delay_ms(50);
	lcd_send_cmd (0x28); /* start to set LCD function */
	delay_ms(50);
	lcd_send_cmd (0x01); /* clear display */
	delay_ms(50);
	lcd_send_cmd (0x06); /* set entry mode */
	delay_ms(50);
	lcd_send_cmd (0x0c); /* set display to on */	
	delay_ms(50);
	lcd_send_cmd (0x02); /* move cursor to home and set data address to 0 */
	delay_ms(50);
	lcd_send_cmd (0x80);

    /* ================================= */
    lcd_goto_XY(0, 0);
    lcd_send_string("Dungnt98");
    lcd_goto_XY(1, 0);
    lcd_send_string("Dungnt98");
}
