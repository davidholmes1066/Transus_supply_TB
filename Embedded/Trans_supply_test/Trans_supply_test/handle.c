#include "handle.h"

float read_ADC(void)
{
	uint16_t TempRes = 0;													//Temporary variable for ADC conversion result
	uint16_t Flags = 0;														//Temporary variable for checking interrupt flag
	float VOLT;																//Voltage conversion
	
	ADCA.CTRLA |= (0x01);													//Enable ADCA
	ADCA.CTRLA |= (0x04);													//Start a conversion on ADCA
	
	while(Flags != 1)														//Wait for conversion
	{
		Flags = (ADCA.INTFLAGS&(0x01));										//Check interrupt flag
	}
	
	TempRes = ADCA.CH0.RES;													//Read ADC conversion
	ADCA.INTFLAGS &= (0x01);												//Clear interrupt flag
	ADCA.CTRLA = (0x00);													//Disables ADCA
	
	VOLT = ((float)TempRes/0xFFF)*MCU_SUP*10;								//Returns conversion result

	return VOLT;
}

void stop_TIMER(void)
{
	TCC4.CTRLA = TC_CLKSEL_OFF_gc;											//Turn timer off
	TCC4.INTCTRLA &= (0xFC);												//Turn interrupt off
	TCC4.CNT = 0;
}

void start_TIMER(void)
{
	TCC4.CNT = 0;
	TCC4.INTCTRLA |= (0x01);												//Turn on overflow interrupt
	TCC4.CTRLA = TC_CLKSEL_DIV8_gc;											//turn on TC and set CLK DIV to 8
}


void enable_DAC(void)
{
	DACA.CTRLA |= DAC_ENABLE_bm;											//Enable DAC
}

void disable_DAC(void)
{
	DACA.CTRLA &= (0xFF&(~DAC_ENABLE_bm));									//Disable DAC
}
