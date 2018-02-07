/*
 * GPIO.h
 *
 *  Created: 1/25/2018 6:16:06 PM
 *  Author: Ahmed Kassem
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>


#define setPort(port, mask) (port) |= (mask)
#define clearPort(port, mask) (port) &= ~(mask)
#define togglePort(port, mask) (port) ^= (mask)

#define setPin(port, pin) (port) |= (1 << pin)
#define clearPin(port, pin) (port) &= ~(1 << pin)
#define togglePin(port, pin) (port) ^= (1 << pin)

#define readPin(port, pin) (GPIO_Read(&port,(1<<pin)) >> pin)
#define readPort(port, mask) GPIO_Read(&port,mask)

#define initPin(port,pin,dir,pullup) GPIO_Init(&port,(1<<pin),dir,pullup)
#define initPort(port,mask,dir,pullup) GPIO_Init(&port,mask,dir,pullup)

typedef void(*EXT_INT_HANDLER)();
extern EXT_INT_HANDLER Interrupt_Callback;

typedef enum {
	Input,
	Output
} Direction;

typedef enum {
	EXT_INT0,
	EXT_INT1,
	EXT_INT2
} EXT_INT_PIN;

typedef enum {
	RISING,
	FALLING,
	LOW,
	ANY_CHANGE
} EXT_INT_MODE ;

void DisableGlobalPullup();
void EnableGlobalPullup();
void GPIO_Init(volatile uint8_t* p, uint8_t pins, Direction dir,uint8_t pullup); 
uint8_t GPIO_Read(volatile uint8_t* p,uint8_t pins); 
void extInterrupt(EXT_INT_PIN pin, EXT_INT_MODE mode, EXT_INT_HANDLER handler);

#endif /* GPIO_H_ */