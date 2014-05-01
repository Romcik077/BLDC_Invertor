/*
 * bldc_ctrl.h
 *
 *  Created on: Mar 15, 2014
 *      Author: proman
 */

#ifndef BLDC_CTRL_H_
#define BLDC_CTRL_H_

#include <avr/io.h>
#include <util/delay.h>
#include <global.h>
#include "hal/timer0/timer0.h"
#include "hal/psc/psc_drv.h"
#include "hal/acmp/acmp.h"

// Maximum period is 64us
#define PWM_PERIOD 5 	//(PWM_PERIOD)/(1/PLL_CLK/1000000);

#define TIMER_PERIOD 100

#define BLDC_START	0
#define BLDC_STOP	1

#define CONV_mS(x)	(unsigned long)x*(1000/TIMER_PERIOD)
#define CONV_uS(x)	(unsigned long)x/TIMER_PERIOD

#define BLDC_CW		0
#define BLDC_CCW	1

#define Ah_Bl	0
#define Ch_Bl	1
#define Ch_Al	2
#define Bh_Al	3
#define Bh_Cl	4
#define Ah_Cl	5

// Initialization of bldc module
void bldcInit(void);

void bldcStart(void);

void bldcStop(void);

// Set pwm duty in percent
void bldcSetPwmDuty(uint8_t duty);



#endif /* BLDC_CTRL_H_ */
