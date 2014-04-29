/*
 * timer0.h
 *
 *  Created on: Jan 24, 2014
 *      Author: proman
 */

#ifndef TIMER0_H_
#define TIMER0_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <global.h>

// Timer/clock prescaler values and timer overflow rates
// tics = rate at which the timer counts up
// 8bitoverflow = rate at which the timer overflows 8bits (or reaches 256)
// 16bit [overflow] = rate at which the timer overflows 16bits (65536)
// 
// overflows can be used to generate periodic interrupts
//
// for 8MHz crystal
// 0 = STOP (Timer not counting)
// 1 = CLOCK		tics= 8MHz			8bitoverflow= 31250Hz		16bit= 122.070Hz
// 2 = CLOCK/8		tics= 1MHz			8bitoverflow= 3906.25Hz		16bit=  15.259Hz
// 3 = CLOCK/64		tics= 125kHz		8bitoverflow=  488.28Hz		16bit=   1.907Hz
// 4 = CLOCK/256	tics= 31250Hz		8bitoverflow=  122.07Hz		16bit=	0.477Hz
// 5 = CLOCK/1024	tics= 7812.5Hz		8bitoverflow=   30.52Hz		16bit=   0.119Hz
// 6 = External Clock on T(x) pin (falling edge)
// 7 = External Clock on T(x) pin (rising edge)

#define TIMER_CLK_STOP			0x00	///< Timer Stopped
#define TIMER_CLK_DIV1			0x01	///< Timer clocked at F_CPU
#define TIMER_CLK_DIV8			0x02	///< Timer clocked at F_CPU/8
#define TIMER_CLK_DIV64			0x03	///< Timer clocked at F_CPU/64
#define TIMER_CLK_DIV256		0x04	///< Timer clocked at F_CPU/256
#define TIMER_CLK_DIV1024		0x05	///< Timer clocked at F_CPU/1024
#define TIMER_CLK_T_FALL		0x06	///< Timer clocked at T falling edge
#define TIMER_CLK_T_RISE		0x07	///< Timer clocked at T rising edge
#define TIMER_PRESCALE_MASK		0x07	///< Timer Prescaler Bit-Mask

// interrupt macros for attaching user functions to timer interrupts
// use these with timerAttach( intNum, function )
#define TIMER0_OVERFLOW_INT			0
#define TIMER0_OUTCOMPAREA_INT		1
#define TIMER0_OUTCOMPAREB_INT		2
#define TIMER0_NUM_INTERRUPTS		3

// default type of interrupt handler to use for timers
// *do not change unless you know what you're doing
// Value may be SIGNAL or ISR
#ifndef TIMER_INTERRUPT_HANDLER
#define TIMER0_INTERRUPT_HANDLER		ISR
#endif

// default initialization routines for each timer
void timer0Init(uint8_t prescale);		///< initialize timer0

// Clock prescaler set/get commands for each timer/counter
// For setting the prescaler, you should use one of the #defines
// above like TIMER_CLK_DIVx, where [x] is the division rate
// you want.
// When getting the current prescaler setting, the return value
// will be the [x] division value currently set.
void timer0SetPrescaler(uint8_t prescale);		///< set timer0 prescaler
uint16_t  timer0GetPrescaler(void);				///< get timer0 prescaler

// TimerAttach and Detach commands
//		These functions allow the attachment (or detachment) of any user function
//		to a timer interrupt.  "Attaching" one of your own functions to a timer
//		interrupt means that it will be called whenever that interrupt happens.
//		Using attach is better than rewriting the actual INTERRUPT() function
//		because your code will still work and be compatible if the timer library
//		is updated.  Also, using Attach allows your code and any predefined timer
//		code to work together and at the same time.  (ie. "attaching" your own
//		function to the timer0 overflow doesn't prevent timerPause from working,
//		but rather allows you to share the interrupt.)
//
//		timerAttach(TIMER1OVERFLOW_INT, myOverflowFunction);
//		timerDetach(TIMER1OVERFLOW_INT)
//
//		timerAttach causes the myOverflowFunction() to be attached, and therefore
//		execute, whenever an overflow on timer1 occurs.  timerDetach removes the
//		association and executes no user function when the interrupt occurs.
//		myOverflowFunction must be defined with no return value and no arguments:
//
//		void myOverflowFunction(void) { ... }
//! Attach a user function to a timer interrupt
void timer0Attach(uint8_t interruptNum, void (*userFunc)(void) );
//! Detach a user function from a timer interrupt
void timer0Detach(uint8_t interruptNum);

// overflow counters
void timer0ClearOverflowCount(void);	///< Clear timer0's overflow counter. 
long timer0GetOverflowCount(void);		///< read timer0's overflow counter

void timer0CTCInit(void);
void timer0CTCSetPeriod(uint8_t period);

/// Enter standard PWM Mode on timer0.
void timer0PWMInit(void);
/// Turn off all timer0 PWM output and set timer mode to normal.
void timer0PWMOff(void);

/// Turn on/off Timer0 PWM outputs.
void timer0PWMAOn(void);			///< Turn on timer0 Channel A (OC0A) PWM output.
void timer0PWMBOn(void);			///< Turn on timer0 Channel B (OC0B) PWM output.
void timer0PWMAOff(void);			///< turn off timer0 Channel A (OC0A) PWM output
void timer0PWMBOff(void);			///< turn off timer0 Channel B (OC0B) PWM output

void timer0PWMASet(uint8_t pwmDuty);	///< set duty of timer0 Channel A (OC0A) PWM output
void timer0PWMBSet(uint8_t pwmDuty);	///< set duty of timer0 Channel B (OC0B) PWM output


#endif /* TIMER0_H_ */
