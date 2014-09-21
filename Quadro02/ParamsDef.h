/*
 * ParamsDef.h
 *
 * Created: 12.06.2013 18:12:21
 *  Author: Слава
 */ 


#ifndef PARAMSDEF_H_
#define PARAMSDEF_H_

#include <stdint.h>

#define SIZEOF_2(X) (sizeof(X)/2)

//typedef double float;

typedef union
{
    float value;
    uint16_t array[SIZEOF_2(float)];
} parametr_t;

#undef SIZEOF_2

#endif /* PARAMSDEF_H_ */