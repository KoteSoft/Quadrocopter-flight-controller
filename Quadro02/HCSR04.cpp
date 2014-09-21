/*
 * HCSR04.c
 *
 * Created: 26.11.2013 17:46:31
 *  Author: Слава
 *	Ультразвуковой высотомер	
 */ 
#include "HCSR04.h"
#include <avr/interrupt.h>
#include "GlobalConstants.h"
#include "Params.h"
#include <stddef.h>

uint8_t HCSR04_Timer_Prescaller;
uint16_t timer0OverflowCount;
uint16_t timer0PrevValue;

ISR(INT0_vect)
{
	if (bit_is_clear(MCUCR, ISC00))
	{
		H.value = (TCNT0 + timer0OverflowCount * 256 - timer0PrevValue) * 16 / 5600.0;
		MCUCR = 1<<ISC01 | 1<<ISC00; //растущий фронт
	} 
	else
	{
		timer0PrevValue = TCNT0 + timer0OverflowCount * 256;
		MCUCR = 1<<ISC01 | 0<<ISC00; //спадающий фронт
	}
}

void INT0_Init()
{
	MCUCR = 1<<ISC01 | 1<<ISC00; //растущий фронт
	GICR = 1<<INT0; 
}