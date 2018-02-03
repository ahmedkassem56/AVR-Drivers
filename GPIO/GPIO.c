/*
 * GPIO.c
 *
 *  Created: 1/25/2018 6:15:55 PM
 *  Author: Ahmed Kassem
 */ 

#include "GPIO.h"
EXT_INT_HANDLER Interrupt_Callback;

void GPIO_Init(volatile uint8_t* p, uint8_t pins, Direction dir,uint8_t pullup) {
	 if (dir == Output)
		*(p-1) |= pins; // PORTX - 1 == DDRX
	else {
		*(p-1) &= ~(pins);
		if (pullup == 1)
			*p |= pins; 
		else
			*p &= ~(pins);
	}
}

uint8_t GPIO_Read(volatile uint8_t* p, uint8_t pins) {
	return *(p-2)&pins; // PORTX - 2 == PINX
}

void EnableGlobalPullup() {
	SFIOR &= ~(1 << PUD); 
}


void DisableGlobalPullup() {
	SFIOR |= (1 << PUD);
}

void extInterrupt(EXT_INT_PIN pin, EXT_INT_MODE mode, EXT_INT_HANDLER handler) {
	Interrupt_Callback = handler; 
	if (pin == EXT_INT0) {
		if (mode == RISING) {
			MCUCR |= (1 << ISC01) | (1 << ISC00); 
		} else if (mode == FALLING) {
			MCUCR |= (1 << ISC01);
			MCUCR &= ~(1 << ISC00); 
		} else if (mode == LOW) {
			MCUCR &= ~((1 << ISC01) | (1 << ISC00));
		} else if (mode == ANY_CHANGE) {
			MCUCR &= ~(1 << ISC01);
			MCUCR |= (1 << ISC00);
		}
		GICR |= (1 << INT0);
	}
	
	else if (pin == EXT_INT1) {
		if (mode == RISING) {
			MCUCR |= (1 << ISC11) | (1 << ISC10);
		} else if (mode == FALLING) {
			MCUCR |= (1 << ISC11);
			MCUCR &= ~(1 << ISC10);
		} else if (mode == LOW) {
			MCUCR &= ~((1 << ISC11) | (1 << ISC10));
		} else if (mode == ANY_CHANGE) {
			MCUCR &= ~(1 << ISC11);
			MCUCR |= (1 << ISC10);
		}
		GICR |= (1 << INT1);
	}	
	else if (pin == EXT_INT2) {
		// TODO
	}
}

ISR(INT0_vect) {
	if (Interrupt_Callback) Interrupt_Callback();
}

ISR(INT1_vect) {
	 // TODO
}


ISR(INT2_vect) {
	// TODO
}
