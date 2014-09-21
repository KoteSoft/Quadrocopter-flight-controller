/* 
* Butterworth.h
*
* Created: 19.06.2014 16:27:23
* Author: Слава
*/

#ifndef __BUTTERWORTH_H__
#define __BUTTERWORTH_H__

#include "ParamsDef.h"

class Butterworth
{
//variables
public:
protected:
private:
	float x_prev, x_pprev, y_prev, y_pprev;
	float fc, fs;
	float w, c, a0, a1, a2, b1, b2;

//functions
public:
	Butterworth();
	Butterworth(float _fc, float _fs);
	~Butterworth();
	float getNext(float x);
	void setFrequencies(float fc, float fs);
}; //Butterworth

#endif //__BUTTERWORTH_H__
