/*
 * timer1.c
 *
 *  Created on: Jan 23, 2014
 *      Author: proman
 */

#include "timer1.h"

// Program ROM constants
// the prescale division values stored in order of timer control register index
// STOP, CLK, CLK/8, CLK/64, CLK/256, CLK/1024
const unsigned short __attribute__ ((progmem)) Timer1PrescaleFactor[] = {0,1,8,64,256,1024};

typedef void (*voidFuncPtr)(void);
volatile static voidFuncPtr Timer1IntFunc[TIMER1_NUM_INTERRUPTS];

void timer1Init(uint8_t _prescaler)
{
	// initialize timer 1
	timer1SetPrescaler(_prescaler);		// set prescaler
	TCNT1 = 0;							// reset TCNT1
}

void timer1SetPrescaler(uint8_t _prescale)
{
	// set prescaler on timer 1
	TCCR1B = ((TCCR1B & ~TIMER_PRESCALE_MASK) | _prescale);
}

uint16_t timer1GetPrescaler(void)
{
	// get the current prescaler setting
	return (pgm_read_word(Timer1PrescaleFactor+(TCCR1B & TIMER_PRESCALE_MASK)));
}

void timer1Attach(uint8_t interruptNum, void (*userFunc)(void) )
{
	// make sure the interrupt number is within bounds
	if(interruptNum < TIMER1_NUM_INTERRUPTS)
	{
		switch (interruptNum) {
			case TIMER1_OVERFLOW_INT:
				sbi(TIMSK1, TOIE1);		// Overflow Interrupt Enable
				break;
			case TIMER1_OUTCOMPAREA_INT:
				sbi(TIMSK1, OCIE1A);	// Output Compare A Match Interrupt Enable
				break;
			case TIMER1_OUTCOMPAREB_INT:
				sbi(TIMSK1, OCIE1B);	// Output Compare B Match Interrupt Enable
				break;
			case TIMER1_INPUTCAPTURE_INT:
				sbi(TIMSK1, ICIE1);		// Input Capture Interrupt Enable
				break;
			default:
				break;
		}
		// set the interrupt function to run
		// the supplied user's function
		Timer1IntFunc[interruptNum] = userFunc;
	}
}

void timer1Detach(uint8_t interruptNum)
{
	// make sure the interrupt number is within bounds
	if(interruptNum < TIMER1_NUM_INTERRUPTS)
	{
		switch (interruptNum) {
			case TIMER1_OVERFLOW_INT:
				cbi(TIMSK1, TOIE1);		// Overflow Interrupt Disable
				break;
			case TIMER1_OUTCOMPAREA_INT:
				cbi(TIMSK1, OCIE1A);	// Output Compare A Match Interrupt Disable
				break;
			case TIMER1_OUTCOMPAREB_INT:
				cbi(TIMSK1, OCIE1B);	// Output Compare B Match Interrupt Disable
				break;
			case TIMER1_INPUTCAPTURE_INT:
				cbi(TIMSK1, ICIE1);		// Input Capture Interrupt Disable
				break;
			default:
				break;
		}
		// set the interrupt function to run nothing
		Timer1IntFunc[interruptNum] = 0;
	}
}

void timer1PWMInit(uint8_t bitRes)
{
	// configures timer1 for use with PWM output
	// on OC1A and OC1B pins

	// enable timer1 as 8,9,10bit PWM
	if(bitRes == 9)
	{	// 9bit mode
		sbi(TCCR1A,WGM11);
		cbi(TCCR1A,WGM10);
	}
	else if( bitRes == 10 )
	{	// 10bit mode
		sbi(TCCR1A,WGM11);
		sbi(TCCR1A,WGM10);
	}
	else
	{	// default 8bit mode
		cbi(TCCR1A,WGM11);
		sbi(TCCR1A,WGM10);
	}

	// clear output compare value A
	OCR1A = 0;
	// clear output compare value B
	OCR1B = 0;
}

void timer1PWMInitICR(uint16_t topcount)
{
	// set PWM mode with ICR top-count
	cbi(TCCR1A,WGM10);
	sbi(TCCR1A,WGM11);
	sbi(TCCR1B,WGM12);
	sbi(TCCR1B,WGM13);

	// set top count value
	ICR1 = topcount;

	// clear output compare value A
	OCR1A = 0;
	// clear output compare value B
	OCR1B = 0;

}

void timer1PWMOff(void)
{
	// set PWM1A/B (OutputCompare action) to none
	timer1PWMAOff();
	timer1PWMBOff();
	// turn off timer1 PWM mode
	cbi(TCCR1A,WGM11);
	cbi(TCCR1A,WGM10);
	cbi(TCCR1B,WGM12);
	cbi(TCCR1B,WGM13);
}

void timer1PWMAOn(void)
{
	// turn on channel A (OC1A) PWM output
	// set OC1A as non-inverted PWM
	sbi(TCCR1A,COM1A1);
	cbi(TCCR1A,COM1A0);
}

void timer1PWMBOn(void)
{
	// turn on channel B (OC1B) PWM output
	// set OC1B as non-inverted PWM
	sbi(TCCR1A,COM1B1);
	cbi(TCCR1A,COM1B0);
}

void timer1PWMAOff(void)
{
	// turn off channel A (OC1A) PWM output
	// set OC1A (OutputCompare action) to none
	cbi(TCCR1A,COM1A1);
	cbi(TCCR1A,COM1A0);
}

void timer1PWMBOff(void)
{
	// turn off channel B (OC1B) PWM output
	// set OC1B (OutputCompare action) to none
	cbi(TCCR1A,COM1B1);
	cbi(TCCR1A,COM1B0);
}

void timer1PWMASet(uint16_t pwmDuty)
{
	// set PWM (output compare) duty for channel A
	// this PWM output is generated on OC1A pin
	// NOTE:	pwmDuty should be in the range 0-255 for 8bit PWM
	//			pwmDuty should be in the range 0-511 for 9bit PWM
	//			pwmDuty should be in the range 0-1023 for 10bit PWM
	//outp( (pwmDuty>>8), OCR1AH);		// set the high 8bits of OCR1A
	//outp( (pwmDuty&0x00FF), OCR1AL);	// set the low 8bits of OCR1A
	OCR1A = pwmDuty;
}

void timer1PWMBSet(uint16_t pwmDuty)
{
	// set PWM (output compare) duty for channel B
	// this PWM output is generated on OC1B pin
	// NOTE:	pwmDuty should be in the range 0-255 for 8bit PWM
	//			pwmDuty should be in the range 0-511 for 9bit PWM
	//			pwmDuty should be in the range 0-1023 for 10bit PWM
	//outp( (pwmDuty>>8), OCR1BH);		// set the high 8bits of OCR1B
	//outp( (pwmDuty&0x00FF), OCR1BL);	// set the low 8bits of OCR1B
	OCR1B = pwmDuty;
}

//! Interrupt handler for tcnt1 overflow interrupt
TIMER_INTERRUPT_HANDLER(TIMER1_OVF_vect)
{
	// if a user function is defined, execute it
	if(Timer1IntFunc[TIMER1_OVERFLOW_INT])
		Timer1IntFunc[TIMER1_OVERFLOW_INT]();
}

//! Interrupt handler for CutputCompare1A match (OC1A) interrupt
TIMER_INTERRUPT_HANDLER(TIMER1_COMPA_vect)
{
	// if a user function is defined, execute it
	if(Timer1IntFunc[TIMER1_OUTCOMPAREA_INT])
		Timer1IntFunc[TIMER1_OUTCOMPAREA_INT]();
}

//! Interrupt handler for OutputCompare1B match (OC1B) interrupt
TIMER_INTERRUPT_HANDLER(TIMER1_COMPB_vect)
{
	// if a user function is defined, execute it
	if(Timer1IntFunc[TIMER1_OUTCOMPAREB_INT])
		Timer1IntFunc[TIMER1_OUTCOMPAREB_INT]();
}

//! Interrupt handler for InputCapture1 (IC1) interrupt
TIMER_INTERRUPT_HANDLER(TIMER1_CAPT_vect)
{
	// if a user function is defined, execute it
	if(Timer1IntFunc[TIMER1_INPUTCAPTURE_INT])
		Timer1IntFunc[TIMER1_INPUTCAPTURE_INT]();
}
