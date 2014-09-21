/*
 * Filters.c
 *
 * Created: 03.07.2013 17:51:41
 *  Author: Слава
 */ 

#include "Filters.h"
#include "GlobalConstants.h"
#include "Butterworth.h"
#include "Params.h"

Butterworth but1, but2, but3, but4;

void filterInit()
{
	but1 = Butterworth(coeffs[FC_BUTTER].value, 244.0);
	but2 = Butterworth(coeffs[FC_BUTTER].value, 244.0);
	but3 = Butterworth(coeffs[FC_BUTTER].value, 244.0);
	but4 = Butterworth(coeffs[FC_BUTTER].value, 244.0);
}

void filterUpdate()
{
	but1.setFrequencies(coeffs[FC_BUTTER].value, 244.0);
	but2.setFrequencies(coeffs[FC_BUTTER].value, 244.0);
	but3.setFrequencies(coeffs[FC_BUTTER].value, 244.0);
	but4.setFrequencies(coeffs[FC_BUTTER].value, 244.0);
}

float LowPassFilter(float new_data, uint8_t filter)
{
	switch (filter)
	{
		case 1: return but1.getNext(new_data);
		case 2: return but2.getNext(new_data);
		case 3: return but3.getNext(new_data);
		default: return 0.0;
	}
}

float ComplemetaryFilter(float alpha, float beta, float factor)
{
	return factor * alpha + (1.0 - factor) * beta;
}
