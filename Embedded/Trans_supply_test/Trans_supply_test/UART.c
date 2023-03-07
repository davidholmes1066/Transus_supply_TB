#include "UART.h"

void init_UART(void)
{
	PORTD_DIRCLR = PIN2_bm;												//Set RX pin USARTE0 D2 as input
	PORTD_DIRSET = PIN3_bm;												//Set TX pin USARTE0 D3 as output
	PORTD_OUTSET = PIN3_bm;												//Set TX pin to high
		
	USARTD0.BAUDCTRLB |= (0x0D<<4);										//Set BSCALE to -3 for baud 115200
	USARTD0.BAUDCTRLA |= (0x83);										//Set BSEL to 131 for baud 115200	

	USARTD0.CTRLC |= (0x03);											//Sets amount of data bits to 8
	USARTD0.CTRLB |= (0x03<<3);											//Sets the Rx and TX enable bits
}

uint8_t read_UART(void)
{
	int test = 0;
	uint8_t garbage;
	uint8_t data;
	
	while(test==0)
	{
		test = USARTD0.STATUS&(0x80);									//keep polling until RXCIF bit is high
	}
	
	data = USARTD0.DATA;												//read the data from the data RX/TX register
	
	while(test!=0)
	{
		test = USARTD0.STATUS&(0x80);									//keep polling until RXCIF bit is low
		garbage = USARTD0.DATA;											//read the data until register is automatically cleared
	}
	
	return data;														//returns 8bit received data
}

void write8_UART(uint8_t data)
{
	int test = 0;
	while(test==0)
	{
		test = USARTD0.STATUS&(0x20);									//keep polling until the data register is ready to receive new data
	}
	
	USARTD0.DATA = data;												//write the 8bits to MATLAB
	
	test = 0;
	while(test==0)
	{
		test = USARTD0.STATUS&(0x20);									//keep polling until the data register is ready to receive new data
	}
}