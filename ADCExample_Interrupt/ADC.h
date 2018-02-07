/*
 * ADC.h
 *
 *  Created: 2/5/2018 1:46:52 PM
 *  Author: Ahmed Kassem
 *
 *  Note: don't use polling (direct) mode and interrupt in the same time.
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

typedef enum {
	ADC0 = 0, // make sure it starts counting from 0
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7
} CHANNEL ;

typedef enum {
	By2 = 0,
	dummy,
	By4,
	By8,
	By16,
	By32,
	By64,
	By128
} PRESCALER ;

typedef enum {
	AREF = 0,
	AVCC = (1 << REFS0),
	INTERNAL = (1 << REFS1) | (1 << REFS0)
} REF_SEL ;

typedef struct {
	uint8_t enabled;
	volatile uint16_t* output;
	uint8_t order;
} INT_CHANNEL ;


/*
 * Function: readADC
 * ----------------------------
 *   Reads ADC directly with polling. May block the code for some clock cycles. 
 *
 *   ch: ADC single ended channel e.g.: ADC0, ADC1,...,ADC7
 *   p: division factor between the XTAL frequency and the input clock to the ADC. e.g.: By128, By64, etc.
 *   ref: voltage reference for the ADC. e.g.: AVCC,AREF and INTERNAL (2.56v)
 *   returns: output of the ADC, 10-bit resolution. (0-1023)
 */
uint16_t readADC(CHANNEL ch, PRESCALER p, REF_SEL ref); 

/*
 * Function: enableADCInterrupt
 * ----------------------------
 *   configures and enables ADC to be used in interrupt mode. 
 *   Note: prescaler and reference are not changed for each channel. They are set for all channels to be used in the interrupt mode.
 *   p: division factor between the XTAL frequency and the input clock to the ADC. e.g.: By128, By64, etc.
 *   ref: voltage reference for the ADC. e.g.: AVCC,AREF and INTERNAL (2.56v)
 *   
 */
void enableADCInterrupt(PRESCALER p, REF_SEL ref); 

/*
 * Function: registerADC
 * ----------------------------
 *   Configures the ADC to begin converting using interrupts. Result is not returned in this function. It only configures and starts the conversion.
 *   Conversion will be updated once after another and will not stop until you unregister the channel using unregisterADC function.
 *   ch: ADC single ended channel e.g.: ADC0, ADC1,...,ADC7
 *   out: pointer to and integer in which the result will be stored in (volatile) 
 */
void registerADC(CHANNEL ch, volatile uint16_t* out); 

/*
 * Function: unregisterADC
 * ----------------------------
 *   Stops the ADC channel from being enabled
 *   Note: this function disables ADC during unregistering the given channel to avoid collisions. 
 *   ch: ADC single ended channel e.g.: ADC0, ADC1,...,ADC7
 *   
 */
void unregisterADC(CHANNEL ch);
 
/*
 * Function: disableADC
 * ----------------------------
 *  Disables ADC peripheral. Should be called if we're not using the ADC for some time to save power. 
 *   
 */
void disableADC();

#endif /* ADC_H_ */