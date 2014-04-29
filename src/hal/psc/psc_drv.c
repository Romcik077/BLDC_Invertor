//! @file psc_drv.c
//!
//! Copyright (c) 2004
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the low level functions for the PSC
//!
//! @version 1.6 (mc100_bldc_sensorless_0_1_0)
//!
//! @todo
//! @bug

//_____  I N C L U D E S ___________________________________________________
#include <avr/io.h>
#include <global.h>
#include "psc_drv.h"
#include "hal/pll/pll_drv.h"

//_____ M A C R O S ________________________________________________________


//_____ P R I V A T E    D E C L A R A T I O N _____________________________


//_____ D E F I N I T I O N ________________________________________________


//_____ D E C L A R A T I O N ______________________________________________

#ifdef USE_PSC0 //!< this define is set on config.h file
//! Configures the PSC0 accordingly to the PSC0 Define Configuration values.
//!
//! @param None.
//!
//! @pre  - Define the configuration in config.h file
//!
//! @post - Set the psc0 comparison values
//!       - Start the PSC0 thanks to Start_psc0() macro
void psc0Init(void)
{
#   if (PSC0_PLL_FREQUENCY == 64)
       pllStart64M();
#   elif (PSC0_PLL_FREQUENCY == 32)
       pllStart32M();
#   elif (PSC0_PLL_FREQUENCY == 0)
#   else
#      error (PSC0_PLL_FREQUENCY should be 0, 32, or 64... See config.h file)
#   endif

#   if (PSC0_OUTPUT_SELECTION == 3)
       psc0EnableBothOutputs();
#   elif (PSC0_OUTPUT_SELECTION == 2)
       Enable_pscout01();
#   elif (PSC0_OUTPUT_SELECTION == 1)
       Enable_pscout00();
#   elif (PSC0_OUTPUT_SELECTION == 0)
       psc0DisableBothOutputs();
#   else
#      error (PSC0_OUTPUT_SELECTION should be 0, 1, 2, or 2... See config.h file)
#   endif

#   if (PSC0_ACTIVE_STATE == 1)
       psc0OutputsActiveHigh();
#   elif (PSC0_ACTIVE_STATE == 0)
       psc0OutputsActiveLow();
#   else
#      error (PSC0_ACTIVE_STATE should be 0, or 1... See config.h file)
#   endif

#   if (PSC0_RAMP_MODE == 4)
       psc0InFourRampMode();
#   elif (PSC0_RAMP_MODE == 2)
       psc0InTwoRampMode();
#   elif (PSC0_RAMP_MODE == 1)
       psc0InOneRampMode();
#   elif (PSC0_RAMP_MODE == 0)
       psc0InCenteredAlignedMode();
#   else
#      error (PSC0_RAMP_MODE should be 0, 1, 3, or 4... See config.h file)
#   endif

#   if (PSC0_FIFTY_PERCENT_MODE == 1)
       psc0EnableFiftyPercentMode();
#   elif (PSC0_FIFTY_PERCENT_MODE == 0)
       psc0DisableFiftyPercentMode();
#   else
#      error (PSC0_FIFTY_PERCENT_MODE should be 0, or 1)
#   endif

#   if (PSC0_SYMETRICAL_FLANK_WIDTH_MODULATION == 1)
       psc0SymetricalFlankWidthModulation();
#   elif (PSC0_SYMETRICAL_FLANK_WIDTH_MODULATION == 0)
       psc0EndOfCycleFlankWidthModulation();
#   else
#      error (PSC0_SYMETRICAL_FLANK_WIDTH_MODULATION should be 0, or 1... See config.h file)
#   endif

#   if (PSC0_AUTOLOCK_MODE == 1)
       psc0EnableAutolockMode();
#   elif (PSC0_AUTOLOCK_MODE == 0)
       psc0DisableAutolockMode();
#   else
#      error (PSC0_AUTOLOCK_MODE should be 0, or 1... See config.h file)
#   endif

#   if (PSC0_PRESCALER_DIVIDER == 256)
       psc0DivideInputClockBy256();
#   elif (PSC0_PRESCALER_DIVIDER == 32)
       psc0DivideInputClockBy32();
#   elif (PSC0_PRESCALER_DIVIDER == 4)
       psc0DivideInputClockBy4();
#   elif (PSC0_PRESCALER_DIVIDER == 0)
       psc0Disableprescaler();
#   else
#      error (PSC0_PRESCALER_DIVIDER should be 0, 4, 16, or 64... See config.h file)
#   endif

#   if (PSC0_PLL_FREQUENCY == 64)
       pllWaitReady();
       psc0UsePllClock();
#   elif (PSC0_PLL_FREQUENCY == 32)
       pllWaitReady();
       psc0UsePllClock();
#   elif (PSC0_PLL_FREQUENCY == 0)
       psc0UseIoClock();
#   else
#      error (PSC0_PLL_FREQUENCY should be 0, 32, or 64... See config.h file)
#   endif
}

//! Update all the PSC0 comparison values accordingly to the four values
//! passed as Psc_comparison_values typedef.
//!
//! @param Comparison values via U16.
//!   psc0Values->deadtime0 (=) U16 deadtime0
//!   psc0Values->ontime0   (=) U16 ontime0
//!   psc0Values->deadtime1 (=) U16 deadtime1
//!   psc0Values->ontime1   (=) U16 ontime1
//!
void psc0Update ( PscValues *psc0Values )
{
#if (PSC0_FIFTY_PERCENT_MODE == 1)
	psc0LockCompareValues();
	OCR0SBH = HIGH(psc0Values->deadtime1);
	OCR0SBL = LOW (psc0Values->deadtime1);
	OCR0RBH = HIGH(psc0Values->ontime1);
	OCR0RBL = LOW (psc0Values->ontime1);
    psc0UpdateCompareValues();
#else
	psc0LockCompareValues();
    OCR0SAH = HIGH(psc0Values->deadtime0);
    OCR0SAL = LOW (psc0Values->deadtime0);
    OCR0RAH = HIGH(psc0Values->ontime0);
    OCR0RAL = LOW (psc0Values->ontime0);
    OCR0SBH = HIGH(psc0Values->deadtime1);
    OCR0SBL = LOW (psc0Values->deadtime1);
    OCR0RBH = HIGH(psc0Values->ontime1);
    OCR0RBL = LOW (psc0Values->ontime1);
    psc0UpdateCompareValues();
#endif
}
#endif // USE_PFC0


#ifdef USE_PSC1 //!< this define is set on config.h file
//! Configures the PSC1 accordingly to the PSC1 Define Configuration values.
//!
//! @param None.
//!
//! @pre  - Define the configuration in config.h file
//!
//! @post - Set the psc1 comparison values
//!       - Start the PSC1 thanks to Start_psc1() macro
void psc1Init(void)
{
#   if (PSC1_PLL_FREQUENCY == 64)
       pllStart64M();
#   elif (PSC1_PLL_FREQUENCY == 32)
       pllStart32M();
#   elif (PSC1_PLL_FREQUENCY == 0)
#   else
#      error (PSC1_PLL_FREQUENCY should be 0, 32, or 64... See config.h file)
#   endif

#   if (PSC1_OUTPUT_SELECTION == 3)
       psc1EnableBothOutputs();
#   elif (PSC1_OUTPUT_SELECTION == 2)
       psc1Enable_out11();
#   elif (PSC1_OUTPUT_SELECTION == 1)
       psc1Enable_out10();
#   elif (PSC1_OUTPUT_SELECTION == 0)
       psc1DisableBothOutputs();
#   else
#      error (PSC1_OUTPUT_SELECTION should be 0, 1, 2, or 2... See config.h file)
#   endif

#   if (PSC1_ACTIVE_STATE == 1)
       psc1OutputsActiveHigh();
#   elif (PSC1_ACTIVE_STATE == 0)
       psc1OutputsActiveLow();
#   else
#      error (PSC1_ACTIVE_STATE should be 0, or 1... See config.h file)
#   endif

#   if (PSC1_RAMP_MODE == 4)
       psc1InFourRampMode();
#   elif (PSC1_RAMP_MODE == 2)
       psc1InTwoRampMode();
#   elif (PSC1_RAMP_MODE == 1)
       psc1InOneRampMode();
#   elif (PSC1_RAMP_MODE == 0)
       psc1InCenteredAlignedMode();
#   else
#      error (PSC1_RAMP_MODE should be 0, 1, 3, or 4... See config.h file)
#   endif

#   if (PSC1_FIFTY_PERCENT_MODE == 1)
       psc1EnableFiftyPercentMode();
#   elif (PSC1_FIFTY_PERCENT_MODE == 0)
       psc1DisableFiftyPercentMode();
#   else
#      error (PSC1_FIFTY_PERCENT_MODE should be 0, or 1)
#   endif

#   if (PSC1_SYMETRICAL_FLANK_WIDTH_MODULATION == 1)
       psc1SymetricalFlankWidthModulation();
#   elif (PSC1_SYMETRICAL_FLANK_WIDTH_MODULATION == 0)
       psc1EndOfCycleFlankWidthModulation();
#   else
#      error (PSC1_SYMETRICAL_FLANK_WIDTH_MODULATION should be 0, or 1... See config.h file)
#   endif

#   if (PSC1_AUTOLOCK_MODE == 1)
       psc1EnableAutolockMode();
#   elif (PSC1_AUTOLOCK_MODE == 0)
       psc1DisableAutolockMode();
#   else
#      error (PSC1_AUTOLOCK_MODE should be 0, or 1... See config.h file)
#   endif

#   if (PSC1_PRESCALER_DIVIDER == 256)
       psc1DivideInputClockBy256();
#   elif (PSC1_PRESCALER_DIVIDER == 32)
       psc1DivideInputClockBy32();
#   elif (PSC1_PRESCALER_DIVIDER == 4)
       psc1DivideInputClockBy4();
#   elif (PSC1_PRESCALER_DIVIDER == 0)
       psc1Disableprescaler();
#   else
#      error (PSC1_PRESCALER_DIVIDER should be 0, 4, 32, or 256... See config.h file)
#   endif

#   if (PSC1_PLL_FREQUENCY == 64)
       pllWaitReady();
       psc1UsePllClock();
#   elif (PSC1_PLL_FREQUENCY == 32)
       Wait_pll_ready();
       psc1UsePllClock();
#   elif (PSC1_PLL_FREQUENCY == 0)
       psc1UseIoClock();
#   else
#      error (PSC1_PLL_FREQUENCY should be 0, 32, or 64... See config.h file)
#   endif
}

//! Update all the PSC1 comparison values accordingly to the four values
//! passed as Psc_comparison_values typedef.
//!
//! @param Comparison values via U16.
//!   psc1Values->deadtime0 (=) U16 deadtime0
//!   psc1Values->ontime0   (=) U16 ontime0
//!   psc1Values->deadtime1 (=) U16 deadtime1
//!   psc1Values->ontime1   (=) U16 ontime1
//!
void psc1Update ( PscValues *psc1Values )
{
#if (PSC1_FIFTY_PERCENT_MODE == 1)
	psc1LockCompareValues();
	OCR1SBH = HIGH(psc1Values->deadtime1);
	OCR1SBL = LOW (psc1Values->deadtime1);
	OCR1RBH = HIGH(psc1Values->ontime1);
	OCR1RBL = LOW (psc1Values->ontime1);
    psc1UpdateCompareValues();
#else
	psc1LockCompareValues();
    OCR1SAH = HIGH(psc1Values->deadtime0);
    OCR1SAL = LOW (psc1Values->deadtime0);
    OCR1RAH = HIGH(psc1Values->ontime0);
    OCR1RAL = LOW (psc1Values->ontime0);
    OCR1SBH = HIGH(psc1Values->deadtime1);
    OCR1SBL = LOW (psc1Values->deadtime1);
    OCR1RBH = HIGH(psc1Values->ontime1);
    OCR1RBL = LOW (psc1Values->ontime1);
    psc1UpdateCompareValues();
#endif
}
#endif // USE_PSC1

#ifdef USE_PSC2 //!< this define is set on config.h file
//! Configures the PSC2 accordingly to the PSC2 Define Configuration values.
//!
//! @param None.
//!
//! @pre  - Define the configuration in config.h file
//!
//! @post - Set the psc2 comparison values
//!       - Start the PSC2 thanks to Start_psc2() macro
void psc2Init(void)
{
#   if (PSC2_PLL_FREQUENCY == 64)
		pllStart64M();
#   elif (PSC2_PLL_FREQUENCY == 32)
		pllStart32M();
#   elif (PSC2_PLL_FREQUENCY == 0)
#   else
#      error (PSC2_PLL_FREQUENCY should be 0, 32, or 64... See config.h file)
#   endif

#   if (PSC2_OUTPUT_SELECTION == 3)
		psc2EnableBothOutputs();
#   elif (PSC2_OUTPUT_SELECTION == 2)
		psc2Enable_out21();
#   elif (PSC2_OUTPUT_SELECTION == 1)
		psc2Enable_out20();
#   elif (PSC2_OUTPUT_SELECTION == 0)
		psc2DisableBothOutputs();
#   else
#      error (PSC2_OUTPUT_SELECTION should be 0, 1, 2, or 2... See config.h file)
#   endif

#   if (PSC2_ACTIVE_STATE == 1)
		psc2OutputsActiveHigh();
#   elif (PSC2_ACTIVE_STATE == 0)
		psc2OutputsActiveLow();
#   else
#      error (PSC2_ACTIVE_STATE should be 0, or 1... See config.h file)
#   endif

#   if (PSC2_RAMP_MODE == 4)
		psc2InFourRampMode();
#   elif (PSC2_RAMP_MODE == 2)
       psc2InTwoRampMode();
#   elif (PSC2_RAMP_MODE == 1)
       psc2InOneRampMode();
#   elif (PSC2_RAMP_MODE == 0)
       psc2InCenteredAlignedMode();
#   else
#      error (PSC2_RAMP_MODE should be 0, 1, 3, or 4... See config.h file)
#   endif

#   if (PSC2_FIFTY_PERCENT_MODE == 1)
       psc2EnableFiftyPercentMode();
#   elif (PSC2_FIFTY_PERCENT_MODE == 0)
       psc2DisableFiftyPercentMode();
#   else
#      error (PSC2_FIFTY_PERCENT_MODE should be 0, or 1)
#   endif

#   if (PSC2_SYMETRICAL_FLANK_WIDTH_MODULATION == 1)
       psc2SymetricalFlankWidthModulation();
#   elif (PSC2_SYMETRICAL_FLANK_WIDTH_MODULATION == 0)
       psc2EndOfCycleFlankWidthModulation();
#   else
#      error (PSC2_SYMETRICAL_FLANK_WIDTH_MODULATION should be 0, or 1... See config.h file)
#   endif

#   if (PSC2_AUTOLOCK_MODE == 1)
       psc2EnableAutolockMode();
#   elif (PSC2_AUTOLOCK_MODE == 0)
       psc2DisableAutolockMode();
#   else
#      error (PSC2_AUTOLOCK_MODE should be 0, or 1... See config.h file)
#   endif

#   if (PSC2_PRESCALER_DIVIDER == 256)
       psc2DivideInputClockBy256();
#   elif (PSC2_PRESCALER_DIVIDER == 32)
       psc2DivideInputClockBy32();
#   elif (PSC2_PRESCALER_DIVIDER == 4)
       psc2DivideInputClockBy4();
#   elif (PSC2_PRESCALER_DIVIDER == 0)
       psc2DisablePrescaler();
#   else
#      error (PSC2_PRESCALER_DIVIDER should be 0, 4, 16, or 64... See config.h file)
#   endif

#   if (PSC2_PLL_FREQUENCY == 64)
       pllWaitReady();
       psc2UsePllClock();
#   elif (PSC2_PLL_FREQUENCY == 32)
       pllWaitReady();
       psc2UsePllClock();
#   elif (PSC2_PLL_FREQUENCY == 0)
       psc2UseIoClock();
#   else
#      error (PSC2_PLL_FREQUENCY should be 0, 32, or 64... See config.h file)
#   endif
}

//! Update all the PSC2 comparison values accordingly to the four values
//! passed as Psc_comparison_values typedef.
//!
//! @param Comparison values via U16.
//!   psc2Values->deadtime0 (=) U16 deadtime0
//!   psc2Values->ontime0   (=) U16 ontime0
//!   psc2Values->deadtime1 (=) U16 deadtime1
//!   psc2Values->ontime1   (=) U16 ontime1
//!
void psc2Update ( PscValues *psc2Values )
{
#if (PSC2_FIFTY_PERCENT_MODE == 1)
	psc2LockCompareValues();
	OCR2SBH = HIGH(psc2Values->deadtime1);
	OCR2SBL = LOW (psc2Values->deadtime1);
	OCR2RBH = HIGH(psc2Values->ontime1);
	OCR2RBL = LOW (psc2Values->ontime1);
    psc2UpdateCompareValues();
#else
    Lock_psc2_compare_values();
    OCR2SAH = HIGH(psc2Values->deadtime0);
    OCR2SAL = LOW (psc2Values->deadtime0);
    OCR2RAH = HIGH(psc2Values->ontime0);
    OCR2RAL = LOW (psc2Values->ontime0);
    OCR2SBH = HIGH(psc2Values->deadtime1);
    OCR2SBL = LOW (psc2Values->deadtime1);
    OCR2RBH = HIGH(psc2Values->ontime1);
    OCR2RBL = LOW (psc2Values->ontime1);
    Update_psc2_compare_values();
#endif
}

#endif // USE_PSC2

void pscUpdateAll(PscValues *pscValues)
{
	psc0LockCompareValues();
	psc1LockCompareValues();
	psc2LockCompareValues();

#if (PSC0_FIFTY_PERCENT_MODE == 1)
	OCR0SBH = HIGH(pscValues->deadtime1);
	OCR0SBL = LOW (pscValues->deadtime1);
	OCR0RBH = HIGH(pscValues->ontime1);
	OCR0RBL = LOW (pscValues->ontime1);
#else
    OCR0SAH = HIGH(psc0Values->deadtime0);
    OCR0SAL = LOW (psc0Values->deadtime0);
    OCR0RAH = HIGH(psc0Values->ontime0);
    OCR0RAL = LOW (psc0Values->ontime0);
    OCR0SBH = HIGH(psc0Values->deadtime1);
    OCR0SBL = LOW (psc0Values->deadtime1);
    OCR0RBH = HIGH(psc0Values->ontime1);
    OCR0RBL = LOW (psc0Values->ontime1);
#endif

#if (PSC1_FIFTY_PERCENT_MODE == 1)
	OCR1SBH = HIGH(pscValues->deadtime1);
	OCR1SBL = LOW (pscValues->deadtime1);
	OCR1RBH = HIGH(pscValues->ontime1);
	OCR1RBL = LOW (pscValues->ontime1);
#else
    OCR1SAH = HIGH(psc1Values->deadtime0);
    OCR1SAL = LOW (psc1Values->deadtime0);
    OCR1RAH = HIGH(psc1Values->ontime0);
    OCR1RAL = LOW (psc1Values->ontime0);
    OCR1SBH = HIGH(psc1Values->deadtime1);
    OCR1SBL = LOW (psc1Values->deadtime1);
    OCR1RBH = HIGH(psc1Values->ontime1);
    OCR1RBL = LOW (psc1Values->ontime1);
#endif

#if (PSC2_FIFTY_PERCENT_MODE == 1)
	OCR2SBH = HIGH(pscValues->deadtime1);
	OCR2SBL = LOW (pscValues->deadtime1);
	OCR2RBH = HIGH(pscValues->ontime1);
	OCR2RBL = LOW (pscValues->ontime1);
#else
    OCR2SAH = HIGH(psc2Values->deadtime0);
    OCR2SAL = LOW (psc2Values->deadtime0);
    OCR2RAH = HIGH(psc2Values->ontime0);
    OCR2RAL = LOW (psc2Values->ontime0);
    OCR2SBH = HIGH(psc2Values->deadtime1);
    OCR2SBL = LOW (psc2Values->deadtime1);
    OCR2RBH = HIGH(psc2Values->ontime1);
    OCR2RBL = LOW (psc2Values->ontime1);
#endif

    psc0UpdateCompareValues();
    psc1UpdateCompareValues();
    psc2UpdateCompareValues();
}
