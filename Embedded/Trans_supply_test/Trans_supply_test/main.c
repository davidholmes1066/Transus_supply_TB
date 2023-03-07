#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>

#include "UART.h"
#include "start.h"
#include "handle.h"
#include "supply.h"

uint16_t GlobOVFCnt;																//Gloabal overflow counter

ISR(TCC4_OVF_vect)																	//Timer counter overflow ISR
{
	TCC4.INTFLAGS |= 0x01;															//Reset OVF interrupt
}


int main(void)
{
	init_CLK();																		//Sets system clock to 32Mhz
	init_UART();																	//Sets UART @ 115200 Baud
	init_ADC();																		//Sets ADC registers
	init_DAC();
	init_TIMER();																	//Sets TIMER registers

	PORTA_DIRSET = PIN0_bm;															//Set LED status pin as output
	PORTA_OUTSET = PIN0_bm;															//Set MCU LED pin

	sei();																			//Enables interrupts
	PMIC.CTRL |= PMIC_LOLVLEN_bm;													//Enable low level interrupts
	
	
	enum CommandList
	{
		CAL,
		ENABLE,
		TEST	
	};

	
	uint8_t command;																//Variable for storing UART commands
	uint16_t TimeMS;																//Variable for storing VDip time in MS
	uint8_t Vlevel;																	//Variable for storing V_out level
	
	uint16_t DAC_P120 = 0;															//Variables for storing DAC data		
	uint16_t DAC_P100 = 0;
	uint16_t DAC_P85 = 0;
	uint16_t DAC_P40 = 0;	

	while (1)
	{
		command = read_UART();														//Fetch command from UART
		switch (command)
		{
			case CAL:																//Perform V_out calibration
				DAC_P120 = Cal_supply(P120);										//Cal V_out @120%
				DAC_P100 = Cal_supply(P100);										//Cal V_out @100%
				DAC_P85 = Cal_supply(P85);											//Cal V_out @85%
				DAC_P40 = Cal_supply(P40);											//Cal V_out @40%
				write8_UART(0xF0);													//Write Finished	
			break;
			
			case ENABLE:															//V_out is set to 24V 
				DACA.CH0DATA = DAC_P100;											//Sets V_out to 100%
				write8_UART(0xF0);													//Write finished
			break;
			
			case TEST:																//Fetch time and level then proceed with test
				TimeMS = (uint16_t)read_UART();										//Get time L
				TimeMS |= ((uint16_t)read_UART()<<8);								//Get time H
				GlobOVFCnt = 0;														//Reset overflows
				start_TIMER();
				Vlevel = read_UART();												//Read Output level
				
				switch (Vlevel)
				{
					case 120:
						DACA.CH0DATA = DAC_P120;									//Set to 120%
						break;
					
					case 100:
						DACA.CH0DATA = DAC_P100;									//Set to 100%
						break;
					
					case 85:
						DACA.CH0DATA = DAC_P85;										//Set to 85%
						break;
					
					case 40:
						DACA.CH0DATA = DAC_P40;										//Set to 40%
						break;
					
					case 0:
						disable_DAC();												//Set to 0%
						break;
					
					default:
						write8_UART(0xFF);											//Return Error
						break;	
				}

				while (GlobOVFCnt < TimeMS)											//Wait for n amount of TC overflows
				{
					//Do nothing
				}
				
				enable_DAC();	
				DACA_CH0DATA = DAC_P100;											//Set to 100%
				stop_TIMER();
				GlobOVFCnt = 0;														//Reset overflow counter
				
				write8_UART(0x0F);													//Write finished
				
				break;
			
			default:																//Return error
				write8_UART(0xFF);
				break;
		}

	}
}