/*
 * UART.h
 *
 * Created: 13/12/2022 13:25:26
 *  Author: Dell Latitude
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <stdint.h>

void init_UART(void);
void write8_UART(uint8_t data);
uint8_t read_UART(void);


#endif /* UART_H_ */