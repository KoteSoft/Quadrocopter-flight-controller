/*
 * ADXL345.c
 *
 * Created: 27.06.2013 13:47:38
 *  Author: Слава
 */ 
#include "ADXL345.h"
#include "main.h"



uint8_t ADXL345_Poll()
{
	uint8_t LSB, MSB;
	
	twi(TWI_START);
	TWDR=ADXL345_ADDR|I2C_WRITE;
	twi(TWI_TRANSMIT);
	TWDR=0x32;
	twi(TWI_TRANSMIT);
	twi(TWI_RESTART);
	TWDR=ADXL345_ADDR|I2C_READ;
	twi(TWI_TRANSMIT);
	twi(TWI_RECEIVE_ACK);
	LSB=TWDR;
	twi(TWI_RECEIVE_ACK);
	MSB=TWDR;
	p_k_y.value = k_y.value;
	k_y.value = LowPassFilter((-0.0032) * (float)(MSB << 8 | LSB), 1);
	k_y.value += coeffs[ADXL345_OFFY].value;
	k_y.value *= coeffs[ADXL345_SCY].value;
	
	twi(TWI_RECEIVE_ACK);
	LSB=TWDR;
	twi(TWI_RECEIVE_ACK);
	MSB=TWDR;
	p_k_x.value = k_x.value;
	k_x.value = LowPassFilter((-0.0032) * (float)(MSB << 8 | LSB), 2);
	k_x.value += coeffs[ADXL345_OFFX].value;
	k_x.value *= coeffs[ADXL345_SCX].value;
	
	twi(TWI_RECEIVE_ACK);
	LSB=TWDR;
	twi(TWI_RECEIVE_NACK);
	MSB=TWDR;
	twi(TWI_STOP);
	p_k_z.value = k_z.value;
	k_z.value = LowPassFilter((0.0032) * (float)(MSB << 8 | LSB), 3);
	k_z.value += coeffs[ADXL345_OFFZ].value;
	k_z.value *= coeffs[ADXL345_SCZ].value;
	
	return 0;
}

uint8_t ADXL345_Init()
{
	twi(TWI_START);
	TWDR=ADXL345_ADDR|I2C_WRITE;
	twi(TWI_TRANSMIT);
	TWDR=0x31;	//DATA_FORMAT
	twi(TWI_TRANSMIT);
	TWDR=0b00001011;
	twi(TWI_TRANSMIT);
	twi(TWI_STOP);
	
	twi(TWI_START);
	TWDR=ADXL345_ADDR|I2C_WRITE;
	twi(TWI_TRANSMIT);
	TWDR=0x2C;	//BW_RATE
	twi(TWI_TRANSMIT);
	TWDR=0b00000111;	//0x09; //0b00001111 rate=50hz, bw=20hz 
	twi(TWI_TRANSMIT);
	twi(TWI_STOP);
	
	twi(TWI_START);
	TWDR=ADXL345_ADDR|I2C_WRITE;
	twi(TWI_TRANSMIT);
	TWDR=0x2D;	//POWER_CTL 
	twi(TWI_TRANSMIT);
	TWDR=0x08;
	twi(TWI_TRANSMIT);
	twi(TWI_STOP);
	return 0;
}

void ADXL345_Calibrate()
{
	coeffs[ADXL345_OFFX].value = coeffs[ADXL345_OFFX].value - k_x.value;
	coeffs[ADXL345_OFFY].value = coeffs[ADXL345_OFFY].value - k_y.value;
	coeffs[ADXL345_OFFZ].value = coeffs[ADXL345_OFFZ].value - k_z.value + 1.0;
	usRegHoldingBuf[MB_OFFSET + MB_ADXL345_OFFX] = coeffs[ADXL345_OFFX].array[0];
	usRegHoldingBuf[MB_OFFSET + MB_ADXL345_OFFX + 1] = coeffs[ADXL345_OFFX].array[1];
	usRegHoldingBuf[MB_OFFSET + MB_ADXL345_OFFY] = coeffs[ADXL345_OFFY].array[0];
	usRegHoldingBuf[MB_OFFSET + MB_ADXL345_OFFY + 1] = coeffs[ADXL345_OFFY].array[1];
	usRegHoldingBuf[MB_OFFSET + MB_ADXL345_OFFZ] = coeffs[ADXL345_OFFZ].array[0];
	usRegHoldingBuf[MB_OFFSET + MB_ADXL345_OFFZ + 1] = coeffs[ADXL345_OFFZ].array[1];
	coeffs[ADXL345_OFFX].value = 0.0;
	coeffs[ADXL345_OFFY].value = 0.0;
	coeffs[ADXL345_OFFZ].value = 0.0;
	//Здесь надо добавить обнуление интегральных сумм гироскопа
}