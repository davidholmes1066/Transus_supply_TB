#include "start.h" 

void init_CLK(void)
{
	OSC.CTRL |= OSC_RC32MEN_bm;												// Enable internal 32 MHz oscillator
	while(!(OSC.STATUS & OSC_RC32MRDY_bm));									// Wait for oscillator is ready
	CCP = CCP_IOREG_gc;														// Security signature to modify clock
	CLK.CTRL = CLK_SCLKSEL_RC32M_gc;										// Select 32 MHz oscillator
	CLK.PSCTRL = CLK_PSADIV_1_gc;											// Set PSA to 1
	CLK.PSCTRL = CLK_PSBCDIV_1_1_gc;										// Set PSB&PSC to 1
}

void init_ADC(void)
{
	PORTA_DIRCLR = PIN3_bm;													//Set PA3 as input
	
	ADCA.PRESCALER = (0x06);												//Set ADCA clock speed to 125kHz
	ADCA.REFCTRL |= ADC_RESOLUTION_12BIT_gc;								//Set ADCA to 12bit resolution
	ADCA.REFCTRL |= ADC_REFSEL_INTVCC_gc;									//Set ADCA reference voltage to supply voltage
	
	ADCA.CH0.MUXCTRL = ADC_CH_MUXPOS_PIN3_gc;								//Multiplexes PA3 to ADCA channel 0
	
	ADCA.CH0.CTRL |= ADC_CH_INPUTMODE_SINGLEENDED_gc;						//Set ADCA channel 0 to single ended input
	ADCA.CH0.MUXCTRL |= ADC_CH_MUXNEG_INTGND_MODE3_gc;						//Set ADCA channel 0 lower reference voltage to internal GND
}

void init_TIMER(void)														//Overflows every 1 ms
{
	TCC4.CTRLB = TC_WGMODE_NORMAL_gc;										//Set timer E0 to normal mode
	TCC4.CTRLA = TC_CLKSEL_OFF_gc;											//Timer is off until CLKSEL is changed
	TCC4.INTCTRLA = TC_OVFINTLVL_LO_gc;										//Set overflow interrupt TCE0 to low level
	TCC4.PER = 0xFA0;														//t = 1ms
}

void init_DAC(void)
{
	DACA.CTRLC = DAC_REFSEL_INT1V_gc;										//set DAC reference to internal 1V
	DACA.CTRLB = DAC_CHSEL_SINGLE_gc;										//set DAC to channel 0 
	DACA.CTRLA = DAC_CH0EN_bm | DAC_ENABLE_bm;								//Enable DAC 
	// Write: to register DACA.CH0DATA 
}