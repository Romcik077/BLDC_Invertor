/*
 * bldc_ctrl.c
 *
 *  Created on: Mar 15, 2014
 *      Author: proman
 */

#include "bldc_ctrl.h"

const uint16_t bldcPwmPeriod = (uint16_t)(PWM_PERIOD / (1/64.0));
const unsigned char bldcCWPhase[] = { Ah_Bl, Ch_Bl, Ch_Al, Bh_Al, Bh_Cl, Ah_Cl };

PscValues bldcPscValues = {0, 0, 0, 0};

unsigned char bldcStatus = BLDC_STOP;
unsigned int periodCounter = 0;
unsigned char bldcPhase = 0;
unsigned int phasePeriod = 12000; // us
unsigned int rumpUpCounter = 0;

void bldcProcesing(void);
void bldcSwitchPhase(unsigned char phase);
void bldcSensorllesPhaseA(void);
void bldcSensorllesPhaseB(void);
void bldcSensorllesPhaseC(void);

void bldcInit(void)
{
	cbi(DDRD, PD1);
	cbi(DDRC, PC2);
	cbi(DDRC, PC3);
	bldcPhase = 0;

	// Initialization of PSC
	psc2Init();
	psc2EnableAutorun();
	psc2DisableFaultMode_out20();
	psc2DisableFaultMode_out21();

	psc1Init();
	psc1EnableAutorun();
	psc1DisableFaultMode_out10();
	psc1DisableFaultMode_out11();

	psc0Init();
	psc0DisableFaultMode_out00();
	psc0DisableFaultMode_out01();

	// Setting the pwm period
	bldcPscValues.ontime1 = bldcPwmPeriod;

	bldcPscValues.deadtime1 = bldcPwmPeriod;
	pscUpdateAll(&bldcPscValues);

	// Initialize ACMP
	acmpInit();
	acmp0SetIntHandler(&bldcSensorllesPhaseA);
	acmp1SetIntHandler(&bldcSensorllesPhaseB);
	acmp2SetIntHandler(&bldcSensorllesPhaseC);

	// Initialize timer0 for speed control
	timer0Init(TIMER_CLK_DIV1024);
	timer0CTCInit();
	timer0CTCSetPeriod(TIMER_PERIOD);// in us
	timer0Attach(TIMER0_OUTCOMPAREA_INT, &bldcProcesing);

	// Starting
	psc0Start();
	sei();
}

void bldcStart(void)
{
//	psc0EnableBothOutputs();
//	psc1EnableBothOutputs();
//	psc2EnableBothOutputs();
	bldcStatus = BLDC_START;
}

void bldcStop(void)
{
	bldcStatus = BLDC_STOP;
}

void bldcSetPwmDuty(uint8_t duty)
{
	if(duty < 0)
		duty = 0;
	if(duty > 100)
		duty = 100;
	bldcPscValues.deadtime1 = bldcPwmPeriod - duty*bldcPwmPeriod/100;
	pscUpdateAll(&bldcPscValues);
}

void bldcProcesing(void)
{
	// TODO excluding period counter
	// TODO create two variant of app with timer and only on interrupt
	periodCounter++;
	rumpUpCounter++;
	if(bldcStatus == BLDC_STOP)
	{
		psc0DisableBothOutputs();
		psc1DisableBothOutputs();
		psc2DisableBothOutputs();
	} else {
		if(periodCounter >= CONV_uS(phasePeriod))
		{
			bldcSwitchPhase(bldcCWPhase[bldcPhase]);
			bldcPhase++;
			if(bldcPhase >= 6)
			{
				bldcPhase = 0;
			}
			periodCounter = 0;
		}
		// TODO move rumpup to function and call at start motor
		if(rumpUpCounter >= CONV_mS(30))
		{
			if(phasePeriod > 5000)
			{
				phasePeriod -= 100;
			}
			rumpUpCounter = 0;
		}
	}
}

void bldcSwitchPhase(unsigned char phase)
{
	psc0DisableBothOutputs();
	psc1DisableBothOutputs();
	psc2DisableBothOutputs();
	switch (phase) {
		case Ah_Bl:
			psc0Enable_out00();
			psc1Enable_out11();
			break;
		case Ch_Bl:
			psc2Enable_out20();
			psc1Enable_out11();
			break;
		case Ch_Al:
			psc2Enable_out20();
			psc0Enable_out01();
			break;
		case Bh_Al:
			psc1Enable_out10();
			psc0Enable_out01();
			break;
		case Bh_Cl:
			psc1Enable_out10();
			psc2Enable_out21();
			break;
		case Ah_Cl:
			psc0Enable_out00();
			psc2Enable_out21();
			break;
		default:
			break;
	}
}

void bldcSensorllesPhaseA(void)
{
	// TODO write formula for calculating 30 degree from rpm
//	timer0CTCSetPeriod(TIMER_PERIOD);// in us
//	timer0Attach(TIMER0_OUTCOMPAREA_INT, &bldcProcesing);
}

void bldcSensorllesPhaseB(void)
{

}

void bldcSensorllesPhaseC(void)
{

}

