/*
 * HCSR04.h
 *
 * Created: 26.11.2013 17:46:09
 *  Author: Слава
 *	Ультразвуковой высотомер
 */ 


#ifndef HCSR04_H_
#define HCSR04_H_

#include <stdint.h>

extern uint8_t HCSR04_Timer_Prescaller;
extern uint16_t timer0OverflowCount;

void INT0_Init();

#endif /* HCSR04_H_ */