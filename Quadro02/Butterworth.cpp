/* 
* Butterworth.cpp
*
* Created: 19.06.2014 16:27:23
* Author: Слава
*/


#include "Butterworth.h"
#include <math.h>

// default constructor
Butterworth::Butterworth()
{
	Butterworth(1.0, 4.0);
} //Butterworth

Butterworth::Butterworth(float _fc, float _fs)
{
	this->fc = _fc;
	this->fs = _fs;
	
	x_prev = 0.0;
	x_pprev = 0.0;
	y_prev = 0.0;
	y_pprev = 0.0;
	
	this->w = tan((M_PI * fc) / fs);
	this->c = 1 + 2 * cos(M_PI_4) * w + w * w;
	this->b2 = (1 - 2 * cos(M_PI_4) * w + w * w) / c;
	this->b1 = (2 * (w * w - 1)) / c;
	this->a2 = (w * w) / c;
	this->a0 = a2;
	this->a1 = 2 * a0;	
}

// default destructor
Butterworth::~Butterworth()
{
} //~Butterworth

float Butterworth::getNext(float x)
{
	float result = a0 * x + a1 * x_prev + a2 * x_pprev - b1 * y_prev - b2 * y_pprev;
	x_pprev = x_prev;
	x_prev = x;
	y_pprev = x_prev;
	y_prev = result;
	
	return result;
}

void Butterworth::setFrequencies(float fc, float fs)
{
	this->fc = fc;
	this->fs = fs;
	
	x_prev = 0.0;
	x_pprev = 0.0;
	y_prev = 0.0;
	y_pprev = 0.0;
	
	w = tan((M_PI * fc) / fs);
	c = 1 + 2 * cos(M_PI_4) * w + w * w;
	b2 = (1 - 2 * cos(M_PI_4) * w + w * w) / c;
	b1 = (2 * (w * w - 1)) / c;
	a2 = (w * w) / c;
	a0 = a2;
	a1 = 2 * a0;
}