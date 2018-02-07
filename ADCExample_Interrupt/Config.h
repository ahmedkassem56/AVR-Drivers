/*
 * lcdConfig.h
 *
 * Created: 2/3/2018 5:36:24 PM
 *  Author: Ahmed Kassem
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

#define F_CPU 1000000UL

//#define LCD_COMPACT_PRINT // disables printf-like lcdPrint

#define LCD_PORT PORTD // high nibble pins of LCD_PORT are LCD data
#define LCD_RS 0 // pin number for RS
#define LCD_RW 1 // pin number for RW
#define LCD_EN 2 // pin number for EN


#endif /* CONFIG_H_ */