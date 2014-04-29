/*
 * timer0.c
 *
 *  Created on: Jan 24, 2014
 *      Author: proman
 */

#include "timer0.h"

// Program ROM constants
// the prescale division values stored in order of timer control register index
// STOP, CLK, CLK/8, CLK/64, CLK/256, CLK/1024
const unsigned short __attribute__ ((progmem)) Timer0PrescaleFactor[] = {0,1,8,64,256,1024};

volatile unsigned long Timer0Reg0;
typedef void (*voidFuncPtr)(void);
volatile static voidFuncPtr Timer0IntFunc[TIMER0_NUM_INTERRUPTS];

void timer0Init(uint8_t prescale)
{
	// initialize timer 0
	timer0SetPrescaler(prescale);			// set prescaler
	TCNT0 = 0;								// reset TCNT0

	timer0ClearOverflowCount();				// initialize time registers
}

void timer0SetPrescaler(uint8_t prescale)
{
	// set prescaler on timer 0
	TCCR0B = ((TCCR0B & ~TIMER_PRESCALE_MASK) | prescale);
}

uint16_t timer0GetPrescaler(void)
{
	// get the current prescaler setting
	return (pgm_read_word(Timer0PrescaleFactor+(TCCR0B & TIMER_PRESCALE_MASK)));
}

void timer0Attach(uint8_t interruptNum, void (*userFunc)(void) )
{
	// make sure the interrupt number is within bounds
	if(interruptNum < TIMER0_NUM_INTERRUPTS)
	{
		switch (interruptNum) {
			case TIMER0_OVERFLOW_INT:
				sbi(TIMSK0, TOIE0);		// Overflow Interrupt Enable
				break;
			case TIMER0_OUTCOMPAREA_INT:
				sbi(TIMSK0, OCIE0A);	// Output Compare A Match Interrupt Enable
				break;
			case TIMER0_OUTCOMPAREB_INT:
				sbi(TIMSK0, OCIE0B);	// Output Compare B Match Interrupt Enable
				break;
			default:
				break;
		}
		// set the interrupt function to run
		// the supplied user's function
		Timer0IntFunc[interruptNum] = userFunc;
	}
}

void timer0Detach(uint8_t interruptNum)
{
	// make sure the interrupt number is within bounds
	if(interruptNum < TIMER0_NUM_INTERRUPTS)
	{
		switch (interruptNum) {
			case TIMER0_OVERFLOW_INT:
				cbi(TIMSK0, TOIE0);		// Overflow Interrupt Enable
				break;
			case TIMER0_OUTCOMPAREA_INT:
				cbi(TIMSK0, OCIE0A);	// Output Compare A Match Interrupt Enable
				break;
			case TIMER0_OUTCOMPAREB_INT:
				cbi(TIMSK0, OCIE0B);	// Output Compare B Match Interrupt Enable
				break;
			default:
				break;
		}
		// set the interrupt function to run nothing
		Timer0IntFunc[interruptNum] = 0;
	}
}

void timer0ClearOverflowCount(void)
{
	// clear the timer overflow counter registers
	Timer0Reg0 = 0;	// initialize time registers
}

long timer0GetOverflowCount(void)
{
	// return the current timer overflow count
	// (this is since the last timer0ClearOverflowCount() command was called)
	return Timer0Reg0;
}

void timer0CTCInit(void)
{
	sbi(TCCR0A, WGM01);
	cbi(TCCR0A, WGM00);
	cbi(TCCR0B, WGM02);

	OCR0A = 0;
}

void timer0CTCSetPeriod(uint8_t period)
{
	//int temp = (F_CPU*((float)period/1000))/(2*timer0GetPrescaler())-1;
	int temp = (F_CPU)/(timer0GetPrescaler()*1000000/period)-1;
	OCR0A = temp;//154;
}

void timer0PWMInit(void)
{
	// configures timer1 for use with PWM output
	// on OC1A and OC1B pins

	// enable timer1 as PWM
	sbi(TCCR0A, WGM01);
	sbi(TCCR0A, WGM00);

	// clear output compare value A
	OCR0A = 0;
	// clear output compare value B
	OCR0B = 0;
}

void timer0PWMOff(void)
{
	// turn off timer1 PWM mode
	cbi(TCCR0A,  WGM01);
	cbi(TCCR0A,  WGM00);
	// set PWM0A/B (OutputCompare action) to none
	timer0PWMAOff();
	timer0PWMBOff();
}

void timer0PWMAOn(void)
{
	// turn on channel A (OC1A) PWM output
	// set OC1A as non-inverted PWM
	sbi(TCCR0A, COM0A1);
	cbi(TCCR0A, COM0A0);
}

void timer0PWMBOn(void)
{
	// turn on channel B (OC1B) PWM output
	// set OC1B as non-inverted PWM
	sbi(TCCR0A, COM0B1);
	cbi(TCCR0A, COM0B0);
}

void timer0PWMAOff(void)
{
	// turn off channel A (OC1A) PWM output
	// set OC1A (OutputCompare action) to none
	cbi(TCCR0A, COM0A1);
	cbi(TCCR0A, COM0A0);
}

void timer0PWMBOff(void)
{
	// turn off channel B (OC1B) PWM output
	// set OC1B (OutputCompare action) to none
	cbi(TCCR0A, COM0B1);
	cbi(TCCR0A, COM0B0);
}

void timer0PWMASet(uint8_t pwmDuty)
{
	OCR0A = pwmDuty;
}

void timer0PWMBSet(uint8_t pwmDuty)
{
	OCR0B = pwmDuty;
}

//! Interrupt handler for tcnt0 overflow interrupt
TIMER0_INTERRUPT_HANDLER(TIMER0_OVF_vect)
{
	Timer0Reg0++;			// increment low-order counter

	// if a user function is defined, execute it too
	if(Timer0IntFunc[TIMER0_OVERFLOW_INT])
		Timer0IntFunc[TIMER0_OVERFLOW_INT]();
}

//! Interrupt handler for OutputCompare0 match (OC0) interrupt
TIMER0_INTERRUPT_HANDLER(TIMER0_COMPA_vect)
{
	// if a user function is defined, execute it
	if(Timer0IntFunc[TIMER0_OUTCOMPAREA_INT])
		Timer0IntFunc[TIMER0_OUTCOMPAREA_INT]();
}

TIMER0_INTERRUPT_HANDLER(TIMER0_COMPB_vect)
{
	// if a user function is defined, execute it
	if(Timer0IntFunc[TIMER0_OUTCOMPAREB_INT])
		Timer0IntFunc[TIMER0_OUTCOMPAREB_INT]();
}
