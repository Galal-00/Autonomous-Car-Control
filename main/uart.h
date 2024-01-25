/*
 * uart.h
 *
 * Created: 8/24/2023
 * Author : Galal
 */ 

#include <avr/io.h>
#include <util/delay.h>

#ifndef UART
#define UART

#define BAUD 9600
#define BAUD_PRESCALE ((F_CPU/16/BAUD) - 1)

void UART_Init()
{
	/* Set baud rate */
	UBRRH = (unsigned char)(BAUD_PRESCALE>>8);
	UBRRL = (unsigned char)BAUD_PRESCALE;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
	/* Set frame format: 8 data bit */
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(3<<UCSZ0);
}

void UART_TxChar(char ch)
{
	while(!(UCSRA & (1<<UDRE)));	// wait for empty transmit buffer
	UDR = ch;
}

char UART_RxChar()
{
	while(!(UCSRA & (1<<RXC)));		// wait until data is received
	return UDR;
}

void UART_SendString(char *str)
{
	unsigned char j=0;
	
	while (str[j]!=0)		/* Send string till null */
	{
		UART_TxChar(str[j]);
		j++;
	}
}
#endif