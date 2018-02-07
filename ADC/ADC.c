/*
 * ADC.c
 *
 *  Created: 2/5/2018 1:46:32 PM
 *  Author: Ahmed Kassem
 */ 
#include "ADC.h"

INT_CHANNEL channels[8];
uint8_t enabled_channels[8] = {0xFF};
uint8_t index_register = 0;
uint8_t index_i = 0,count = 0;

void enableADCInterrupt(PRESCALER p, REF_SEL ref) {
	ADCSRA |= (1 << ADEN); // enable ADC
	sei();
	ADCSRA |= (1 << ADIE); // activates ADC interrupt
	ADCSRA &= ~((1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2)); // reset prescaler bits (if it's already written before)
	ADCSRA |= p; // the pre-defined enum matches bits configuration
	ADMUX = 0;
	ADMUX |= ref;
	
	for (int i = 0; i < 8; i++) {
		channels[i].enabled = 0;
		channels[i].output = 0;
	}
	
}

void registerADC(CHANNEL ch, volatile uint16_t* out) {
	if (channels[ch].enabled == 0) {
		enabled_channels[index_register] = ch;
		channels[ch].enabled = 1;
		channels[ch].output = out;
		DDRA &= ~ (1 << ch);
		if (count == 0) { // conversion didn't start (first ADC to be registered)
			index_i = index_register;
			ADMUX |= ch;
			ADCSRA |= (1 << ADSC);
		}
		index_register++;
		count++;
	}
}

void unregisterADC(CHANNEL ch) {
	if (channels[ch].enabled == 1) {
		ADCSRA &= ~(1 << ADIE); // disable ADC interrupt
		while (!(ADCSRA & (1 << ADIF))); // wait till current conversion is complete
		channels[ch].enabled = 0;
		// rebuild arrays, indexes and counters
		index_register = 0; 
		index_i = 0;
		count = 0;
		
		for (int i = 0; i < 8; i++) {  // rebuild enabled_channels array
			enabled_channels[i] = 0xFF; 
			if (channels[i].enabled) {
				enabled_channels[index_register] = i;
				index_register++;
				count++;
			}
		}
		ADCSRA |= (1 << ADIE); // re-enable ADC interrupt
		if (count > 0) {
			ADCSRA |= (1 << ADSC);
		}
	}
}

ISR(ADC_vect) {
	uint8_t ch = enabled_channels[index_i];
	*channels[ch].output = ADCL;
	*channels[ch].output |= (ADCH << 8);
	if (count > 0) {
		if (++index_i >= count) index_i = 0; 
		ch = enabled_channels[index_i];
		ADMUX &= ~ ((1 << MUX0) | (1 << MUX1) | (1 << MUX2) | (1 << MUX3) | (1 << MUX4));
		ADMUX |= ch;
		ADCSRA |= (1 << ADSC);
	} 
}

uint16_t readADC(CHANNEL ch, PRESCALER p, REF_SEL ref) {
	ADCSRA |= (1 << ADEN); // enable ADC
	ADCSRA &= ~((1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2)); // reset prescaler bits (if it's already written before) 
	ADCSRA |= p; // the pre-defined enum matches bits configuration  
	DDRA &= ~ (1 << ch);
	ADMUX = 0x00; // reset ADMUX
	ADMUX |= ref | ch;
	ADCSRA |= (1 << ADSC); // initiate conversion 
	while (!(ADCSRA & (1 << ADIF))); // wait till flag is raised 
	uint16_t result = ADCL; 
	result |= (ADCH << 8); 
	return result;
}