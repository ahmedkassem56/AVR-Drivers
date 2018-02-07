/*
 * ADCExample_Interrupt.c
 *
 * Created: 2/7/2018 6:18:46 PM
 * Author : Ahmed Kassem
 */ 

#include <avr/io.h>
#include "LCD.h"
#include "GPIO.h"
#include "ADC.h"

volatile uint16_t x[8] = {0};

int main(void)
{
	initLCD(); 
	
	enableADCInterrupt(By128, AVCC); 
	
	registerADC(ADC0,&x[0]); // ADC0-7 will be converted using interrupts and results are stored in x[0-7]
	registerADC(ADC1,&x[1]);
	registerADC(ADC2,&x[2]);
	registerADC(ADC3,&x[3]);	
	registerADC(ADC4,&x[4]);
	registerADC(ADC5,&x[5]);
	registerADC(ADC6,&x[6]);
	registerADC(ADC7,&x[7]);

	initPin(PORTD,3,Input,1);
	initPin(PORTB,0,Input,1);
	
    while (1) 
    {

		lcdResetCursor();
		lcdPrint("%d:%d:%d:%d         ", x[0],x[1],x[2],x[3]); 
		lcdSetCursor(1,2);
		lcdPrint("%d:%d:%d:%d         ", x[4],x[5],x[6],x[7]); 
		
		static int last_key = 0; // push button on PD3 disables ADC4-7
		int key = readPin(PORTD,3); 
		if (key == 0 && last_key) {
			unregisterADC(ADC4);
			unregisterADC(ADC5);
			unregisterADC(ADC6);
			unregisterADC(ADC7);
		}
		last_key = key;
		
		static int last_key2 = 0; // push button on PB0 re-enables ADC4-7. 
		int key2 = readPin(PORTB,0);
		if (key2 == 0 && last_key2) {
			registerADC(ADC4,&x[4]);
			registerADC(ADC5,&x[5]);
			registerADC(ADC6,&x[6]);
			registerADC(ADC7,&x[7]);
		}
		last_key2 = key2;
    }
}

