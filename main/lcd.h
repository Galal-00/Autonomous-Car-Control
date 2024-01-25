#include <avr/io.h>
#include <util/delay.h>

#define LCD_DATA PORTA // port B is selected as LCD data port
#define CTRL PORTB // port A is selected as LCD command port

#define en PB7 // enable signal is connected to port A pin 7
#define rw PB6 // read/write signal is connected to port A pin 6
#define rs PB5 // register select signal is connected to port A pin 5

void init_LCD(void)
{
	LCD_cmd(0x38); // initialization in 8bit mode of 16X2 LCD
	_delay_ms(1);

	LCD_cmd(0x01); // make clear LCD
	_delay_ms(1);

	LCD_cmd(0x02); // return home
	_delay_ms(1);

	LCD_cmd(0x06); // make increment in cursor
	_delay_ms(1);

	LCD_cmd(0x80); // "8" go to first line and "0" is for 0th position
	_delay_ms(1);

	return;
}

void LCD_cmd(unsigned char cmd)
{
	LCD_DATA = cmd; // data lines are set to send command
	
	CTRL &= ~(1 << rs); // RS sets 0, for command data
	CTRL &= ~(1 << rw); // RW sets 0, to write data
	CTRL |= (1 << en); // make enable high
	
	_delay_ms(100);
	CTRL &= ~(1 << en); // make enable low

	return;
}

void LCD_write(unsigned char data)
{
	LCD_DATA = data; // data lines are set to send command
	CTRL |= (1 << rs); // RS sets 1, for typing data
	CTRL &= ~(1 << rw); // RW sets 0, to write data
	CTRL |= (1 << en); // make enable high

	_delay_ms(1);
	CTRL &= ~(1 << en); // make enable low

	return;
}

void LCD_write_string(char* data_str)
{
	int i = 0;
	while(data_str[i] != 0)		/* Write string till null */
	{
		LCD_write(data_str[i]);
		i++;
	}
}

void LCD_clear_line(int line_num)
{
	//assume the LCD is 32x2
	if(line_num == 1) LCD_cmd(0x80);	//force cursor to beginning of 1st line
	else LCD_cmd(0xC0);					//force cursor to beginning of 2nd line
	for(int i = 0; i < 32; i++)
	{
		LCD_write(0);
	}
}