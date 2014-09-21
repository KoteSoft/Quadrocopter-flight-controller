/*
 * Filters.h
 *
 * Created: 03.07.2013 17:51:01
 *  Author: Слава
 */ 


#ifndef FILTERS_H_
#define FILTERS_H_

#include "ParamsDef.h"

float LowPassFilter(float new_data, uint8_t filter);
float ComplemetaryFilter(float alpha, float beta, float factor);
void filterInit();
void filterUpdate();

#endif /* FILTERS_H_ */