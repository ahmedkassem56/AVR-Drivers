/*
 * LCD.c
 *
 *  Created: 1/26/2018 4:16:07 PM
 *  Author: Ahmed Kassem
 *
 *  To use float numbers in lcdPrint function (this adds ~2kB of code space) follow this: https://startingelectronics.org/articles/atmel-AVR-8-bit/print-float-atmel-studio-7/
 */ 

#include "LCD.h"

void initLCD() {
	initPort(LCD_PORT,0xF0,Output,0); // high nibble pins of LCD_PORT are data inputs to LCD 
	initPort(LCD_PORT,(1 << LCD_RS) | (1 << LCD_EN) | (1 << LCD_RW),Output,0); // RS,EN,RW pins are output
	clearPin(LCD_PORT,LCD_EN); // make sure enable pin is low
	_delay_us(2000); 
	lcdCommand(0x33); // setting up 4bits mode 
	_delay_us(100);
	lcdCommand(0x32); // setting up 4bits mode
	_delay_us(100);
	lcdCommand(0x28); // 4 bits - 2 lines mode
	_delay_us(100); 
	lcdCommand(0x0E); // Display on - cursor blinking
	_delay_us(100); 
	lcdCommand(0x01); // Clear display
	_delay_us(2000); 
	lcdCommand(0x06); // increment cursor
	_delay_us(100);
}

void lcdCommand(uint8_t cmd) {
	uint8_t h_cmd = cmd & 0xF0; // masking high nibble 
	clearPort(LCD_PORT,0xF0); // clear high nibble 
	setPort(LCD_PORT,h_cmd); // set high nibble with high nibble of the command 
	clearPin(LCD_PORT,LCD_RS); // RS = 0 for command 
	clearPin(LCD_PORT,LCD_RW); // RW = 0 for write 
	setPin(LCD_PORT,LCD_EN); // create falling edge [1/2] 
	_delay_us(1); 
	clearPin(LCD_PORT,LCD_EN); // create falling edge [2/2] 
	_delay_us(100);
	h_cmd = (cmd << 4) & 0xF0; // swap nibbles 
	clearPort(LCD_PORT,0xF0); // clear high nibble
	setPort(LCD_PORT,h_cmd); // set high nibble with high nibble of the command
	clearPin(LCD_PORT,LCD_RS); // RS = 0 for command
	clearPin(LCD_PORT,LCD_RW); // RW = 0 for write
	setPin(LCD_PORT,LCD_EN); // create falling edge [1/2]
	_delay_us(1);
	clearPin(LCD_PORT,LCD_EN); // create falling edge [2/2]
	_delay_us(100);
}

void lcdData(uint8_t data) {
	uint8_t h_cmd = data & 0xF0; // masking high nibble
	clearPort(LCD_PORT,0xF0); // clear high nibble
	setPort(LCD_PORT,h_cmd); // set high nibble with high nibble of the command
	clearPin(LCD_PORT,LCD_RS); // RS = 0 for command
	clearPin(LCD_PORT,LCD_RW); // RW = 0 for write
	setPin(LCD_PORT,LCD_EN); // create falling edge [1/2]
	_delay_us(1);
	clearPin(LCD_PORT,LCD_EN); // create falling edge [2/2]
	_delay_us(100);
	h_cmd = (data << 4) & 0xF0; // swap nibbles
	clearPort(LCD_PORT,0xF0); // clear high nibble
	setPort(LCD_PORT,h_cmd); // set high nibble with high nibble of the command
	setPin(LCD_PORT,LCD_RS); // RS = 1 for data
	clearPin(LCD_PORT,LCD_RW); // RW = 0 for write
	setPin(LCD_PORT,LCD_EN); // create falling edge [1/2]
	_delay_us(1);
	clearPin(LCD_PORT,LCD_EN); // create falling edge [2/2]
	_delay_us(100);
}

void lcdClear() {
	lcdCommand(0x01);
	_delay_us(2000);
}

void lcdResetCursor() {
	lcdCommand(0x02);
}

void lcdSetCursor(uint8_t x,uint8_t y) {
	if (y == 1)
		y = 0x80;
	else if(y == 2)
		y = 0xC0;
	lcdCommand(x+y-1);
		
}

#ifndef LCD_COMPACT_PRINT
void lcdPrint(const char *format, ...) {
	char buffer[256]; // STEP 1: building the string
	va_list args;
	va_start (args, format);
	vsnprintf (buffer,256,format, args);
	va_end(args);
	for (int i = 0;buffer[i];i++) // STEP 2: printing the string
		lcdData(buffer[i]);
}

#else
void lcdPrint(char *data) {
	for (int i = 0;data[i];i++) 
		lcdData(data[i]);
}
#endif