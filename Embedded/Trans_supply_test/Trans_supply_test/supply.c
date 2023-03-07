#include "supply.h"

uint16_t Cal_supply(float volt)
{
	float ReadVolt = 0;															//Temp storage for ADC conversion
	uint16_t DacData = 0;														//Temp storage for DacData
	
	DACA.CH0DATA = DacData;														//Set DAC to 0
	
	while((ReadVolt < volt)&&(DacData < 0xFFFF))
	{
		ReadVolt = read_ADC();													//Read V_out
		DacData++;																//Increase V_out by one DAC step	
	}
	
	return DacData;																//Return DAC data for V_out is ~volt
}
