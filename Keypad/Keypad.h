/*
 * Keypad.h
 *
 *  Created: 2/4/2018 5:27:21 PM
 *  Author: Ahmed Kassem
 
 *  Note:This library is built for a 4x3 Keypad but can be easily modified to larger scale up to 8x8 by editing ROW_PINS and LINE_PINS in Keypad.c and adding corresponding 
 *  defines for ROWx,LINEx,ROW_MASK and LINE_MASK. No need to edit anything in functions.
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define F_CPU 1000000UL

#include "GPIO.h"
#include <util/delay.h>

extern uint8_t ROW_PINS[4]; 
	
#define ROW0 ROW_PINS[0]
#define ROW1 ROW_PINS[1]
#define ROW2 ROW_PINS[2]
#define ROW3 ROW_PINS[3]
#define ROW_MASK ((1 << ROW0) | (1 << ROW1) | (1 << ROW2) | (1 << ROW3))

extern uint8_t LINE_PINS[3];
	
#define LINE0 LINE_PINS[0]
#define LINE1 LINE_PINS[1]
#define LINE2 LINE_PINS[2]
#define LINE_MASK ((1 << LINE0) | (1 << LINE1) | (1 << LINE2))


void initKeypad(); 
uint8_t keypadScan(); 

#endif /* KEYPAD_H_ */