#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>


void init_CLK(void);							//Sets system clock to 32MHz
void init_ADC(void);							//Sets ADC registers
void init_TIMER(void);							//Sets registers 1ms Timer
void init_DAC(void);							//Sets DAC registers

