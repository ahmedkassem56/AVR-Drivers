/*
 * ADC.h
 *
 *  Created: 2/5/2018 1:46:52 PM
 *  Author: Ahmed Kassem
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

typedef enum {
	ADC0 = 0, // make sure it starts counting from 0
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7
} CHANNEL ;

typedef enum {
	By2 = 0,
	dummy,
	By4,
	By8,
	By16,
	By32,
	By64,
	By128
} PRESCALER ;

typedef enum {
	AREF = 0,
	AVCC = (1 << REFS0),
	INTERNAL = (1 << REFS1) | (1 << REFS0)
} REF_SEL ;

uint16_t readADC(CHANNEL ch, PRESCALER p, REF_SEL ref);

#endif /* ADC_H_ */