#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>

#define VSUP 24

#define P120 (VSUP/100)*120													//Calculate V_out for 120% of supply voltage
#define P100 VSUP																//Calculate V_out for 100% of supply voltage
#define P85 (VSUP/100)*85														//Calculate V_out for 85% of supply voltage
#define P40 (VSUP/100)*40														//Calculate V_out for 40% of supply voltage
#define P0 0																	//Calculate V_out for 0% of supply voltage
 


#ifndef SUPPLY_H_
#define SUPPLY_H_


uint16_t Cal_supply(float volt);


#endif /* SUPPLY_H_ */