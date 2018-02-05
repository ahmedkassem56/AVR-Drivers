/*
 * Keypad.c
 *
 *  Created: 2/4/2018 5:27:37 PM
 *  Author: Ahmed Kassem
  
 *  Note:This library is built for a 4x3 Keypad but can be easily modified to larger scale up to 8x8 by editing ROW_PINS and LINE_PINS in Keypad.c, adding corresponding
 *  defines for ROWx,LINEx,ROW_MASK,LINE_MASK and editing "keys" array. No need to edit anything in functions.
 */ 

#include "Keypad.h"

#define ROW_PORT PORTC                // port connected to keypad rows
uint8_t ROW_PINS[4] = {0, 1, 2, 3};   // pins connected to keypad rows (in the same order as in "keys" array)

#define LINE_PORT PORTC               // port connected to keypad lines
uint8_t LINE_PINS[3] = {4, 5, 6};     // pins connected to keypad lines (in the same order as in "keys" array)

#define DEBOUNCE_ENABLE // comment to disable debounce delay	


const unsigned char keys[sizeof(ROW_PINS)][sizeof(LINE_PINS)] = {{'1','2','3'}
													            ,{'4','5','6'}
															    ,{'7','8','9'}
															    ,{'*','0','#'}};

void initKeypad() {
	initPort(ROW_PORT,ROW_MASK,Output,0); // initialize row pins as output
	setPort(ROW_PORT,ROW_MASK);           // initialize output to high
	
	initPort(LINE_PORT,LINE_MASK,Input,1); // initialize line pins as input
}

uint8_t keypadScan() {
	uint8_t row = 0,line = 0, broke = 0;
	clearPort(ROW_PORT,ROW_MASK); // enable all row pins (set them low)
	uint8_t col = readPort(LINE_PORT,LINE_MASK);  // read all line pins
	if (col != LINE_MASK) { // if any line is enabled the output will not be equal to the mask since there will be a zero in it. 
#ifdef DEBOUNCE_ENABLE
		_delay_us(20);  // delay to debounce the button
#endif
		for (int i = 0; i < sizeof(ROW_PINS);i++) {
			setPort(ROW_PORT,ROW_MASK); // disable all rows (set high)
			clearPin(ROW_PORT,ROW_PINS[i]); // enable only one row at a time
			for (int j = 0; j < sizeof(LINE_PINS);j++) { // loop on all lines to detected if any is enabled
				if (!readPin(LINE_PORT,LINE_PINS[j])) { // if a line is enabled it will be read low
					line = j; // we found the pressed key at 'j' line and 'i' row
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
