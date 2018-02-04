/*
 * Keypad.c
 *
 *  Created: 2/4/2018 5:27:37 PM
 *  Author: Ahmed Kassem
 */ 

#include "Keypad.h"

#define ROW_PORT PORTC
uint8_t ROW_PINS[4] = {0, 1, 2, 3};

#define LINE_PORT PORTC
uint8_t LINE_PINS[3] = {4, 5, 6};

#define DEBOUNCE_ENABLE // comment to disable debounce delay	


const unsigned char keys[sizeof(ROW_PINS)][sizeof(LINE_PINS)] = {{'1','2','3'}
													            ,{'4','5','6'}
															    ,{'7','8','9'}
															    ,{'*','0','#'}};

void initKeypad() {
	initPort(ROW_PORT,ROW_MASK,Output,0); 
	setPort(ROW_PORT,ROW_MASK);
	
	initPort(LINE_PORT,LINE_MASK,Input,1);
}

uint8_t keypadScan() {
	uint8_t row = 0,line = 0, broke = 0;
	clearPort(ROW_PORT,ROW_MASK);
	uint8_t col = readPort(LINE_PORT,LINE_MASK); 
	if (col != LINE_MASK) {
#ifdef DEBOUNCE_ENABLE
		_delay_us(20);
#endif
		for (int i = 0; i < sizeof(ROW_PINS);i++) {
			setPort(ROW_PORT,ROW_MASK);
			clearPin(ROW_PORT,ROW_PINS[i]);
			for (int j = 0; j < sizeof(LINE_PINS);j++) {
				if (!readPin(LINE_PORT,LINE_PINS[j])) {
					line = j;
					row = i;
					broke = 1;
					break; // break the inner loop
				}
			}
			if (broke) // break the outer loop
				break;
		}
		if (!broke) return 0;
		return keys[row][line];
	}
	return 0;
}
