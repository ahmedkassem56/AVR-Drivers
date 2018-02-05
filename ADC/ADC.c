/*
 * ADC.c
 *
 *  Created: 2/5/2018 1:46:32 PM
 *  Author: Ahmed Kassem
 */ 
#include "ADC.h"


uint16_t readADC(CHANNEL ch, PRESCALER p, REF_SEL ref) {
	ADCSRA |= (1 << ADEN); // enable ADC
	ADCSRA &= ~((1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2)); // reset prescaler bits (if it's already written before) 
	ADCSRA |= p; // the pre-defined enum matches bits configuration  
	//initPin(PORTA,ch,Input,0); // initialize ADC pin as input
	DDRA &= ~ (1 << ch);
	ADMUX |= ref | ch;
	ADCSRA |= (1 << ADSC); // initiate conversion 
	while (!(ADCSRA & (1 << ADIF))); // wait till flag is raised 
	uint16_t result = ADCL; 
	result |= (ADCH << 8); 
	return result;
}