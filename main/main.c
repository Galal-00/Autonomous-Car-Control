/*
 * main.c
 *
 * Created: 8/24/2023 5:42:39 PM
 * Author : Galal
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "control.h"

ISR(USART_RXC_vect)
{
	/* received message causes interrupt */
	while(!(UCSRA & (1<<RXC)));
	char received = UDR;
	message_handler(received);
}

int timer_counter = 0;

ISR(TIMER2_OVF_vect)
{
	timer_counter++;
	TCNT2 = 177;	// reset the timer
	if(timer_counter >= 100)
	{
		lcd_print_time();
		timer_counter = 0;
	}
}

int main(void)
{
    UART_Init();
	DDRA = 0xFF; // set LCD data port as output for LCD
	DDRB = 0xE0; // set LCD signals (RS, RW, E) as output for LCD
	DDRB |= (1<<PB1) | (1<<PB2);	// set output pins to DC motor H-bridge
	DDRC |= (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3);	// set output pins to stepper motor H-bridge
	
	init_LCD(); // initialize LCD
	LCD_cmd(0x0C); // display on, cursor off
	LCD_cmd(0xC0);	// go to second line
	LCD_write_string("Time: 00:00:00");
	
	pwm_init();
	
	sei();
    while (1) 
    {
		
    }
}