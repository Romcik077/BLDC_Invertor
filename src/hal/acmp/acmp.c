/*
 * acmp.c
 *
 *  Created on: Mar 11, 2014
 *      Author: proman
 */

#include "acmp.h"

typedef void (*voidFunc)(void);
volatile static voidFunc acmp0IntHandler = 0, acmp1IntHandler = 0, acmp2IntHandler = 0;

void acmpInit(void)
{
	ACSR = (0 << ACCKDIV);

	AC0CON = (0 << AC0EN)|(1 << AC0IE)|(0 << AC0IS1)|(0 << AC0IS0)|
			 (1 << AC0M2)|(0 << AC0M1)|(0 << AC0M0);

	AC1CON = (0 << AC1EN)|(1 << AC1IE)|(0 << AC1IS1)|(0 << AC1IS0)|
			 (1 << AC1M2)|(0 << AC1M1)|(0 << AC1M0);

	AC2CON = (0 << AC2EN)|(1 << AC2IE)|(0 << AC2IS1)|(0 << AC2IS0)|
			 (1 << AC2M2)|(0 << AC2M1)|(0 << AC2M0);
}

void acmpStart(void)
{
	sbi(AC0CON, AC0EN);
	sbi(AC1CON, AC1EN);
	sbi(AC2CON, AC2EN);
}

void acmpStop(void)
{
	cbi(AC0CON, AC0EN);
	cbi(AC1CON, AC1EN);
	cbi(AC2CON, AC2EN);
}

void acmp0SetIntHandler(void (*handlerFunc)(void))
{
	acmp0IntHandler = handlerFunc;
}

void acmp1SetIntHandler(void (*handlerFunc)(void))
{
	acmp1IntHandler = handlerFunc;
}

void acmp2SetIntHandler(void (*handlerFunc)(void))
{
	acmp2IntHandler = handlerFunc;
}

ISR(ANALOG_COMP_0_vect)
{
	if(acmp0IntHandler != 0)
	{
		acmp0IntHandler();
	}
}

ISR(ANALOG_COMP_1_vect)
{
	if(acmp1IntHandler != 0)
	{
		acmp1IntHandler();
	}
}

ISR(ANALOG_COMP_2_vect)
{
	if(acmp2IntHandler != 0)
	{
		acmp2IntHandler();
	}
}
