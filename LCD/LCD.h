/*
 * LCD.h
 *
 *  Created: 1/26/2018 4:16:19 PM
 *  Author: Ahmed Kassem
 *
 *  To use float numbers in lcdPrint function (this adds ~2kB of code space) follow this: https://startingelectronics.org/articles/atmel-AVR-8-bit/print-float-atmel-studio-7/
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "Config.h"
#include "GPIO.h"

#include <util/delay.h>
#include <stdint.h>

#ifndef LCD_COMPACT_PRINT
#include <stdarg.h>
#include <stdio.h>
#endif

void initLCD(); 
void lcdCommand(uint8_t cmd); 
void lcdData(uint8_t data);
void lcdClear(); 
void lcdResetCursor();
void lcdSetCursor(uint8_t x,uint8_t y);

#ifndef LCD_COMPACT_PRINT
void lcdPrint(const char *format, ...); 
#else 
void lcdPrint(char *data);
#endif

#endif /* LCD_H_ */