/*
 * GPIO.c
 *
 *  Created: 1/25/2018 6:15:55 PM
 *  Author: Ahmed Kassem
 */ 

#include "GPIO.h"
EXT_INT_HANDLER Interrupt_Callback;

void GPIO_Init(PORT p, uint8_t pins, Direction dir,uint8_t pullup) {
	switch (p) {
		case PORTA__:
	 	if (dir == Output)
			DDRA |= pins;
		else {
			DDRA &= ~(pins);
			if (pullup == 1)
				PORTA |= pins; 
			else
				PORTA &= ~(pins);
		}
		break;
		
		case PORTB__:
	 	if (dir == Output)
	 		DDRB |= pins;
	 	else {
		 	DDRB &= ~(pins);
		 	if (pullup == 1)
		 		PORTB |= pins;
		 	else
		 		PORTB &= ~(pins);
	 	}
	 	break;
		 
		case PORTC__:
	 	if (dir == Output)
	 		DDRC |= pins;
	 	else {
		 	DDRC &= ~(pins);
		 	if (pullup == 1)
		 		PORTC |= pins;
		 	else
		 		PORTC &= ~(pins);
	 	}
	 	break;
		 
		case PORTD__:
	 	if (dir == Output)
	 		DDRD |= pins;
	 	else {
		 	DDRD &= ~(pins);
		 	if (pullup == 1)
		 		PORTD |= pins;
		 	else
		 		PORTD &= ~(pins);
	 	}
	 	break;
	}
}

uint8_t GPIO_Read(PORT p, uint8_t pins) {
	switch (p) {
		case PORTA__: 
			return (PINA & pins); 
			break;
		case PORTB__:
			return (PINB & pins);
			break;
		case PORTC__:
			return (PINC & pins);
			break;
		case PORTD__:
			return (PIND & pins); 
			break;
	}
	return 0;
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
}

ISR(INT0_vect) {
	if (Interrupt_Callback) Interrupt_Callback();
}

ISR(INT1_vect) {
	if (Interrupt_Callback) Interrupt_Callback();
}
