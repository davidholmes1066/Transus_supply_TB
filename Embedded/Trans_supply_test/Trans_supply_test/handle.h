#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>


#ifndef HANDLE_H_
#define HANDLE_H_

#define MCU_SUP 3.3

float read_ADC(void);
void stop_TIMER(void);
void start_TIMER(void);
void disable_DAC(void);
void enable_DAC(void);

#endif /* HANDLE_H_ */