//! @file psc_drv.h
//!
//! Copyright (c) 2004
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the low level macros and definition for the PSC use
//!
//! @version 1.7 (mc100_bldc_sensorless_0_1_0)
//!
//! @todo
//! @bug

#ifndef PSC_DRV_H
#define PSC_DRV_H

//_____  I N C L U D E S ___________________________________________________
#include "hal/pll/pll_drv.h"

//! @defgroup PSC_modules PSC Modules
//! PSC Modules
//! @{

/* Configurations for PSC modules
 * 	Un-comment for enable module
 */
#define USE_PSC0
#define USE_PSC1
#define USE_PSC2

/* Frequency of CLK for modules
 * 	64 - 64MHz
 * 	32 - 32Mhz
 * 	0 - IO CLK
 */
#define PSC0_PLL_FREQUENCY 64
#define PSC1_PLL_FREQUENCY 64
#define PSC2_PLL_FREQUENCY 64

/* Output configurations:
 * 	3 - Enable_both_psc0_outputs
 * 	2 - Enable_pscout01
 * 	1 - Enable_pscout00
 * 	0 - Disable_both_psc0_outputs
 */
#define PSC0_OUTPUT_SELECTION 0
#define PSC1_OUTPUT_SELECTION 0
#define PSC2_OUTPUT_SELECTION 0

/* Fifty set:
 * 	1 - Enable
 * 	0 - Disable
 */
#define PSC0_FIFTY_PERCENT_MODE 1
#define PSC1_FIFTY_PERCENT_MODE 1
#define PSC2_FIFTY_PERCENT_MODE 1

/* Set active state for output
 * 	1 - high active state
 * 	0 - low active state
 */
#define PSC0_ACTIVE_STATE 1
#define PSC1_ACTIVE_STATE 1
#define PSC2_ACTIVE_STATE 1

/* Set PSC ramp mode:
 * 	4 - four ramps
 * 	2 - two ramps
 * 	1 - one ramp
 * 	0 - center aligned mode
 */
#define PSC0_RAMP_MODE 1
#define PSC1_RAMP_MODE 1
#define PSC2_RAMP_MODE 1

/* Set PSC flank modulation:
 * 	1 - enable
 * 	0 - disable
 */
#define PSC0_SYMETRICAL_FLANK_WIDTH_MODULATION 0
#define PSC1_SYMETRICAL_FLANK_WIDTH_MODULATION 0
#define PSC2_SYMETRICAL_FLANK_WIDTH_MODULATION 0

/* Set AutoLock:
 *  1 - enable
 *  0 - disable
 */
#define PSC0_AUTOLOCK_MODE 0
#define PSC1_AUTOLOCK_MODE 0
#define PSC2_AUTOLOCK_MODE 0

/* Set prescaler for PSC module
 * 	256 - PSC_CLK/256
 * 	32 - PSC_CLK/32
 * 	4 - PSC_CLK/4
 * 	0 - no prescaler
 */
#define PSC0_PRESCALER_DIVIDER 0
#define PSC1_PRESCALER_DIVIDER 0
#define PSC2_PRESCALER_DIVIDER 0

//_____ M A C R O S ________________________________________________________

   //! @defgroup PSC0_macros PSC0 Macros
   //! PSC0 Macros
   //! @{

      //! @defgroup PSC0_output_configuration PSC0 Output Configuration
      //! Select the PSC0 Outputs
      //! @{
#define psc0Enable_out00()						(PSOC0 |=  (1<<POEN0A) )  //!< Enable PSC0 Waveform Generator A
#define psc0Disable_out00()						(PSOC0 &= ~(1<<POEN0A) )  //!< Disable PSC0 Waveform Generator A

#define psc0Enable_out01()						(PSOC0 |=  (1<<POEN0B) )  //!< Enable PSC0 Waveform Generator B
#define psc0Disable_out01()						(PSOC0 &= ~(1<<POEN0B) )  //!< Disable PSC0 Waveform Generator B
//! Enable Both PSC0 Waveform Generator A and B
#define psc0EnableBothOutputs()					(PSOC0 |=  ((1<<POEN0A) | (1<<POEN0B)))
//! Disable Both PSC0 Waveform Generator A and B
#define psc0DisableBothOutputs()				(PSOC0 &= ~((1<<POEN0A) | (1<<POEN0B)))

#define psc0OutputsActiveHigh()					(PCNF0 |=  (1<<POP0) )    //!< PSC0 outputs are active low
#define psc0OutputsActiveLow()					(PCNF0 &= ~(1<<POP0) )    //!< PSC0 outputs are active high
      //! @}

      //! @defgroup SPC0_mode_control_module PSC0 Mode Control
      //! PSC0C Mode ontrol
      //! @{
#define psc0EnableFiftyPercentMode()			(PCNF0 |=  (1<<PFIFTY0) )  //!< PSC0 is in 50% mode: Only OCR0RBH/L and OCR0SBH/L are used. They are duplicated in OCR0R/SAH/L during the update of OCR0BH/L
#define psc0DisableFiftyPercentMode()			(PCNF0 &= ~(1<<PFIFTY0) )  //!< OCR0R/SAH/L and OCR0R/SBH/L are fully independant

#define psc0EnableAutolockMode()				(PCNF0 |=  (1<<PALOCK0) )  //!< OCR0R/SAH/L and OCR0R/SBH/L can be written without disturbing the PSC cycle. The update of these registers will be proceed at the end of the PSC cycle if the OCR0RB has been last written
#define psc0DisableAutolockMode()				(PCNF0 &= ~(1<<PALOCK0) )  //!< The update will be procced according to PLOCK0 bit

#define psc0LockCompareValues()					(PCNF0 |=  (1<<PLOCK0) )   //!< Take care that the lock is active only if you have disabled the autolock mode
#define psc0UpdateCompareValues()				(PCNF0 &= ~(1<<PLOCK0) )   //!< The compare registers will be updated with the content of OCR0ARH/L and OCR0BRH
      //! @}

      //! @defgroup PSC0_clock_control PSC0 Clock Control
      //! PSC0 Clock Control
      //! @{

         //! @defgroup PSC0_clock_selection PSC0 Clock Selection
         //! PSC0 Clock Selection
         //! @{
//! Connect the PSC0 input clock to the PLL
#define psc0UsePllClock()                          (PCNF0 |= (1<<PCLKSEL0) )
//! Connect the PSC0 input clock to the I/O clock
#define psc0UseIoClock()                           (PCNF0 &= ~(1<<PCLKSEL0) )
//! Start the PLL at 64MHz and connect it to PSC0
#define psc0Use64megaPllClock()			\
          (Start_pll_64_mega(),			\
           Wait_pll_ready(),			\
           Psc0_use_pll_clock() )
//! Start the PLL at 32MHz and connect it to PSC0
#define psc0Use32megaPllClock()			\
          (Start_pll_32_mega(),			\
           Wait_pll_ready(),			\
           Psc0_use_pll_clock() )
         //! @}

         //! @defgroup PSC0_prescaler_control PSC0 Prescaler Control
         //! PSC0 Prescaler Control
         //! @{
//! No PSC0prescaler
#define psc0Disableprescaler()				(PCTL0 &= ~(  (1<<PPRE01) | (1<<PPRE00) ) )
//! PSC0 clock is internally divided by 4
#define psc0DivideInputClockBy4()			(PCTL0 &= ~(1<<PPRE01),PCTL0 |=  (1<<PPRE00) )
//! PSC0 clock is internally divided by 32
#define psc0DivideInputClockBy32()			(PCTL0 |=  (1<<PPRE01),PCTL0 &= ~(1<<PPRE00) )
//! PSC0 clock is internally divided by 256
#define psc0DivideInputClockBy256()			(PCTL0 |=  ((1<<PPRE01) | (1<<PPRE00)) )
         //! @}

      //! @}

      //! @defgroup PSC0_ramp_mode_selection PSC0 Ramp Mode Selection
      //! PSC0 Ramp Mode Selection
      //! @{
//! PSC0 is configured in one ramp mode, it means that the internal counter
//! counts from 0 up to OCR0RB
#define psc0InOneRampMode()			(PCNF0 &= ~(  (1<<PMODE01) | (1<<PMODE00) ) )
//! PSC0 is configured in two ramp mode, it means that the internal counter
//! counts from 0 up to OCR0RA then from 0 to OCR0RB
#define psc0InTwoRampsMode()		(PCNF0 &= ~(1<<PMODE01),PCNF0 |=  (1<<PMODE00) )
//! PSC0 is configured in for ramp mode, it means that the internal counter
//! counts from 0 up to OCR0SA then from 0 to OCR0RA then from 0 to OCR0SB then from 0 to OCR0RB
#define psc0InFourRampsMode()		(PCNF0 |=  (1<<PMODE01),PCNF0 &= ~(1<<PMODE00) )
//! PSC0 is configured in for ramp mode, it means that the internal counter
//! counts from 0 up to OCR0RB then from OCR0RB downto 0
#define psc0InCenteredAlignedMode()	(PCNF0 |=  (  (1<<PMODE01) | (1<<PMODE00) ) )
      //! @}

      //! @defgroup PSC0_flank_width_modulation_configuration PSC0 Flank Width Modulation Configuration
      //! Select PSC0 Flank Width Modulation Configuration
      //! @{
#define psc0SymetricalFlankWidthModulation()		(PCTL0 |=  (1<<PBFM0) )     //!< PSC0 Flank width modulation operates on both OCR0RA and OCR0RB
#define psc0EndOfCycleFlankWidthModulation()		(PCTL0 &= ~(1<<PBFM0) )     //!< PSC0 Flank width modulation operates only on OCR0RB
      //! @}

      //! @defgroup PSC0_adc_amplifier_trigger_configuration PSC0 ADC Amplifier Trigger Configuration
      //! Select the PSC0 trigger configuration for the ADC or the amplifier
      //! @{
//! The PSC0 synchronization signal is sent to the ADC/Amplifier on waveform generator A leading edge
#define psc0SynchroOnWaveformGeneratorALeadingEdge()                   \
           (PSCO0 &= ~(  (1<<PSYNC01) | (1<<PSYNC00) ) )
//! The PSC0 synchronization signal is sent to the ADC/Amplifier on waveform generator A trailing edge
#define psc0SynchroOnWaveformGeneratorATrailingEdge()                  \
           (PSCO0 &= ~(1<<PSYNC01),                                           \
            PSCO0 |=  (1<<PSYNC00) )
//! The PSC0 synchronization signal is sent to the ADC/Amplifier on waveform generator B leading edge
#define psc0SynchroOnWaveformGeneratorBLeadingEdge()                   \
           (PSCO0 |=  (1<<PSYNC01),                                           \
            PSCO0 &= ~(1<<PSYNC00) )
//! The PSC0 synchronization signal is sent to the ADC/Amplifier on waveform generator B trailing edge
#define psc0SynchroOnWaveformGeneratorBTrailingEdge()                  \
           (PSCO0 |=  (  (1<<PSYNC01) | (1<<PSYNC00) ) )
      //! @}

      //! @defgroup PSC0_run_control PSC0 Run Control
      //! Turn On and Off the PSC0
      //! @{
#define psc0Start()                                  (PCTL0 |=  (1<<PRUN0) )     //!< Turn On PSC0
#define psc0Stop()                                   (PCTL0 &= ~(1<<PRUN0) )     //!< Turn Off PSC0
//! Turn Off PSC0 and the end of cycle
#define psc0CompleteWaveformAndStop()             (PCTL0 |=  (1<<PCCYC0), \
                                                       PCTL0 &= ~(1<<PRUN0) )
#define psc0IsStarted()                             (PCTL0 & (1<<PRUN0) )
      //! @}

      //! @defgroup PSC0_fault_mode_configuration PSC0 Fault Mode Configuration
      //! PSC0 Fault Mode Configuration
      //! @{
#define psc0EnableFaultMode_out00()                  (PCTL0 |=  (1<<PAOC0A) )    //!< Fault input select to block A can act directly to PSCOUT00 output
#define psc0DisableFaultMode_out00()                 (PCTL0 &= ~(1<<PAOC0A) )    //!< No fault or retrigger management on PSCOUT00

#define psc0EnableFaultMode_out01()                  (PCTL0 |=  (1<<PAOC0B) )    //!< Fault input select to block A can act directly to PSCOUT00 output
#define psc0DisableFaultMode_out01()                 (PCTL0 &= ~(1<<PAOC0B) )    //!< No fault or retrigger management on PSCOUT01

#define psc0EnableAutorun()                         (PCTL0 |=  (1<<PARUN0) )    //!< Setting PRUN2 in PCTL2 register or setting both PARUN2 in PCTL2 register and PRUN1 in PCTL1 register will make the two PSC start simultaneously
#define psc0DisableAutorun()                        (PCTL0 &= ~(1<<PARUN0) )    //!< No synchronization between PSC2 and PSC0 exists
      //! @}

      //! @defgroup PSC0_interrupt_configuration PSC0 Interrupt Configuration
      //! PSC0 interrupt configuration
      //! @{
#define psc0EnableSynchroErrorInterrupt()         (PIM0 |=  (1<<PSEIE0) )     //!< An interrupt is generated when the PSEI0 bit is set
#define psc0DisableSynchroErrorInterrupt()        (PIM0 &= ~(1<<PSEIE0) )     //!< No interrupt is generated when the PSEI0 bit is set

#define psc0EnableExternalEventAInterrupt()      (PIM0 |=  (1<<PEVE0A) )     //!< An external event which can generate a capture from retrigger/fault block A generates an interrupt
#define psc0DisableExternalEventAInterrupt()     (PIM0 &= ~(1<<PEVE0A) )     //!< An external event which can generate a capture from retrigger/fault block A doesn't generate any interrupt

#define psc0EnableExternalEventBInterrupt()      (PIM0 |=  (1<<PEVE0B) )     //!< An external event which can generate a capture from retrigger/fault block B generates an interrupt
#define psc0DisableExternalEventBInterrupt()     (PIM0 &= ~(1<<PEVE0B) )     //!< An external event which can generate a capture from retrigger/fault block B doesn't generate any interrupt

#define psc0EnableEndOfCycleInterrupt()          (PIM0 |=  (1<<PEOPE0) )     //!< An interrupt is generated when PSC0 reaches the end of the whole cycle
#define psc0DisableEndOfCycleInterrupt()         (PIM0 &= ~(1<<PEOPE0) )     //!< No interrupt is generated when PSC0 reaches the end of the whole cycle
      //! @}

      //! @defgroup PSC0_interrupt_flag_control PSC0 Interrupt Flag Control
      //! PSC0 interrupt flag control
      //! @{
#define psc0IsSynchroErrorInterruptFlagSet()    (PIFR0 & (1<<PSEI0) )       //!< Return 1 if the PSEI0 bit in PIFR0 is set
#define psc0ClearSynchroErrorInterruptFlag()     (PIFR0 &= ~(1<<PSEI0) )     //!< Clear PSEI0 bit in PIFR0 register

#define psc0IsExternalEventAInterruptFlagSet() (PIFR0 & (1<<PEV0A) )       //!< Return 1 if the PEV0A bit in PIFR0 is set
#define psc0ClearExternalEventAInterruptFlag()  (PIFR0 &= ~(1<<PEV0A) )     //!< Clear PEV0A bit in PIFR0 register

#define psc0IsExternalEventBInterruptFlagSet() (PIFR0 & (1<<PEV0B) )       //!< Return 1 if the PEV0B bit in PIFR0 is set
#define psc0ClearExternalEventBInterruptFlag()  (PIFR0 &= ~(1<<PEV0B) )     //!< Clear PEV0B bit in PIFR0 register

#define psc0IsEndOfCycleInterruptFlagSet()     (PIFR0 & (1<<PEOP2) )       //!< Return 1 if the PE0P2 bit in PIFR0 is set
#define psc0ClearEndOfCycleInterruptFlag()      (PIFR0 &= ~(1<<PEOP2) )     //!< Clear PEOP2 bit in PIFR0 register
      //! @}

   //! @}


   //! @defgroup PSC1_macros PSC1 Macros
   //! PSC1 Macros
   //! @{

      //! @defgroup PSC1_output_configuration PSC1 Output Configuration
      //! Select the PSC1 Outputs
      //! @{
#define psc1Enable_out10()                             (PSOC1 |=  (1<<POEN1A) )  //!< Enable PSC1 Waveform Generator A
#define psc1Disable_out10()                            (PSOC1 &= ~(1<<POEN1A) )  //!< Disable PSC1 Waveform Generator A

#define psc1Enable_out11()                             (PSOC1 |=  (1<<POEN1B) )  //!< Enable PSC1 Waveform Generator B
#define psc1Disable_out11()                            (PSOC1 &= ~(1<<POEN1B) )  //!< Disable PSC1 Waveform Generator B
//! Enable Both PSC1 Waveform Generator A and B
#define psc1EnableBothOutputs()					(PSOC1 |=  ((1<<POEN1A) | (1<<POEN1B)))
//! Disable Both PSC1 Waveform Generator A and B
#define psc1DisableBothOutputs()				(PSOC1 &= ~((1<<POEN1A) | (1<<POEN1B)))

#define psc1OutputsActiveHigh()                    (PCNF1 |=  (1<<POP1) )    //!< PSC1 outputs are active low
#define psc1OutputsActiveLow()                     (PCNF1 &= ~(1<<POP1) )    //!< PSC1 outputs are active high
      //! @}

      //! @defgroup PSC1_mode_control_module PSC1 Mode Control
      //! PSC1 Mode Control
      //! @{
#define psc1EnableFiftyPercentMode()              (PCNF1 |=  (1<<PFIFTY1) )  //!< PSC1 is in 50% mode: Only OCR1RBH/L and OCR1SBH/L are used. They are duplicated in OCR1R/SAH/L during the update of OCR1BH/L
#define psc1DisableFiftyPercentMode()             (PCNF1 &= ~(1<<PFIFTY1) )  //!< OCR1R/SAH/L and OCR1R/SBH/L are fully independant

#define psc1EnableAutolockMode()                   (PCNF1 |=  (1<<PALOCK1) )  //!< OCR1R/SAH/L and OCR1R/SBH/L can be written without disturbing the PSC cycle. The update of these registers will be proceed at the end of the PSC cycle if the OCR1RB has been last written
#define psc1DisableAutolockMode()                  (PCNF1 &= ~(1<<PALOCK1) )  //!< The update will be procced according to PLOCK1 bit

#define psc1LockCompareValues()                    (PCNF1 |=  (1<<PLOCK1) )   //!< Take care that the lock is active only if you have disabled the autolock mode
#define psc1UpdateCompareValues()                  (PCNF1 &= ~(1<<PLOCK1) )   //!< The compare registers will be updated with the content of OCR1AH/L and OCR1BH
      //! @}

      //! @defgroup PSC1_clock_control PSC1 Clock Control
      //! PSC1 Clock Control
      //! @{

         //! @defgroup PSC1_clock_selection PSC1 Clock Selection
         //! PSC1 Clock Selection
         //! @{
//! Connect the PSC1 input clock to the PLL
#define psc1UsePllClock()                          (PCNF1 |= (1<<PCLKSEL0) )
//! Connect the PSC1 input clock to the I/O clock
#define psc1UseIoClock()                           (PCNF1 &= ~(1<<PCLKSEL0) )
//! Start the PLL at 64MHz and connect it to psc1
#define psc1Use64megaPllClock()                                          \
          (Start_pll_64_mega(),                                               \
           Wait_pll_ready(),                                                  \
           psc1_use_pll_clock() )
//! Start the PLL at 32MHz and connect it to psc1
#define psc1Use32megaPllClock()                                          \
          (Start_pll_32_mega(),                                               \
           Wait_pll_ready(),                                                  \
           psc1_use_pll_clock() )
         //! @}

         //! @defgroup psc1_prescaler_control psc1 Prescaler Control
         //! psc1 Prescaler Control
         //! @{
//! No psc1prescaler
#define psc1Disableprescaler()				(PCTL1 &= ~(  (1<<PPRE11) | (1<<PPRE10) ) )
//! PSC1 clock is internally divided by 4
#define psc1DivideInputClockBy4()			(PCTL1 &= ~(1<<PPRE11),PCTL1 |=  (1<<PPRE10) )
//! PSC1 clock is internally divided by 32
#define psc1DivideInputClockBy32()			(PCTL1 |=  (1<<PPRE11),PCTL1 &= ~(1<<PPRE10) )
//! PSC1 clock is internally divided by 256
#define psc1DivideInputClockBy256()			(PCTL1 |=  ((1<<PPRE11) | (1<<PPRE10)) )
         //! @}

      //! @}

      //! @defgroup PSC1_ramp_mode_selection PSC1 Ramp Mode Selection
      //! PSC1 Ramp Mode Selection
      //! @{
      //! PSC1 is configured in one ramp mode, it means that the internal counter
      //! counts from 0 up to OCR1RB
#define psc1InOneRampMode()					(PCNF1 &= ~(  (1<<PMODE11) | (1<<PMODE10) ) )
//! PSC1 is configured in two ramp mode, it means that the internal counter
//! counts from 0 up to OCR1RA then from 0 to OCR1RB
#define psc1InTwoRampMode()					(PCNF1 &= ~(1<<PMODE11),PCNF1 |=  (1<<PMODE10) )
//! PSC1 is configured in for ramp mode, it means that the internal counter
//! counts from 0 up to OCR1SA then from 0 to OCR1RA then from 0 to OCR1SB then from 0 to OCR1RB
#define psc1InFourRampMode()				(PCNF1 |=  (1<<PMODE11),PCNF1 &= ~(1<<PMODE10) )
//! PSC1 is configured in for ramp mode, it means that the internal counter
//! counts from 0 up to OCR1RB then from OCR1RB downto 0
#define psc1InCenteredAlignedMode()			(PCNF1 |=  (  (1<<PMODE11) | (1<<PMODE10) ) )
      //! @}

      //! @defgroup PSC1_flank_width_modulation_configuration PSC1 Flank Width Modulation Configuration
      //! Select PSC1 Flank Width Modulation Configuration
      //! @{
#define psc1SymetricalFlankWidthModulation()      (PCTL1 |=  (1<<PBFM1) )     //!< PSC1 Flank width modulation operates on both OCR1RA and OCR1RB
#define psc1EndOfCycleFlankWidthModulation()    (PCTL1 &= ~(1<<PBFM1) )     //!< PSC1 Flank width modulation operates only on OCR1RB
      //! @}

      //! @defgroup PSC1_adc_amplifier_trigger_configuration PSC1 ADC Amplifier Trigger Configuration
      //! Select the PSC1 trigger configuration for the ADC or the amplifier
      //! @{
//! The PSC1 synchronization signal is sent to the ADC/Amplifier on waveform generator A leading edge
#define psc1SynchroOnWaveformGeneratorALeadingEdge()                   \
           (PSCO1 &= ~(  (1<<PSYNC11) | (1<<PSYNC10) ) )
//! The PSC1 synchronization signal is sent to the ADC/Amplifier on waveform generator A trailing edge
#define psc1SynchroOnWaveformGeneratorATrailingEdge()                  \
           (PSCO1 &= ~(1<<PSYNC11),                                           \
            PSCO1 |=  (1<<PSYNC10) )
//! The PSC1 synchronization signal is sent to the ADC/Amplifier on waveform generator B leading edge
#define psc1SynchroOnWaveformGeneratorBLeadingEdge()                   \
           (PSCO1 |=  (1<<PSYNC11),                                           \
            PSCO1 &= ~(1<<PSYNC10) )
//! The psc1 synchronization signal is sent to the ADC/Amplifier on waveform generator B trailing edge
#define psc1SynchroOnWaveformGeneratorBTrailingEdge()                  \
           (PSCO1 |=  (  (1<<PSYNC11) | (1<<PSYNC10) ) )
      //! @}

      //! @defgroup PSC1_run_control PSC1 Run Control
      //! Turn On and Off the PSC1
      //! @{
#define psc1Start()                                  (PCTL1 |=  (1<<PRUN1) )     //!< Turn On PSC1
#define psc1Stop()                                   (PCTL1 &= ~(1<<PRUN1) )     //!< Turn Off PSC1
//! Turn Off PSC1 and the end of cycle
#define psc1CompleteWaveformAndStop()             (PCTL1 |=  (1<<PCCYC1), \
                                                       PCTL1 &= ~(1<<PRUN1) )
#define psc1IsStarted()                             (PCTL1 & (1<<PRUN1) )
      //! @}

      //! @defgroup PSC1_fault_mode_configuration PSC1 Fault Mode Configuration
      //! PSC1 Fault Mode Configuration
      //! @{
#define psc1EnableFaultMode_out10()                  (PCTL1 |=  (1<<PAOC1A) )    //!< Fault input select to block A can act directly to PSCOUT00 output
#define psc1DisableFaultMode_out10()                 (PCTL1 &= ~(1<<PAOC1A) )    //!< No fault or retrigger management on PSCOUT00

#define psc1EnableFaultMode_out11()                  (PCTL1 |=  (1<<PAOC1B) )    //!< Fault input select to block A can act directly to PSCOUT00 output
#define psc1DisableFaultMode_out11()                 (PCTL1 &= ~(1<<PAOC1B) )    //!< No fault or retrigger management on PSCOUT01

#define psc1EnableAutorun()                         (PCTL1 |=  (1<<PARUN1) )    //!< Setting PRUN0 in PCTL0 register or setting both PARUN0 in PCTL0 register and PRUN2 in PCTL2 register will make the two PSC start simultaneously
#define psc1DisableAutorun()                        (PCTL1 &= ~(1<<PARUN1) )    //!< No synchronization between PSC2 and PSC1 exists
      //! @}

      //! @defgroup PSC1_interrupt_configuration PSC1 Interrupt Configuration
      //! PSC1 interrupt configuration
      //! @{
#define psc1EnableSynchroErrorInterrupt()         (PIM1 |=  (1<<PSEIE1) )     //!< An interrupt is generated when the PSEI0 bit is set
#define psc1DisableSynchroErrorInterrupt()        (PIM1 &= ~(1<<PSEIE1) )     //!< No interrupt is generated when the PSEI0 bit is set

#define psc1EnableExternalEventAInterrupt()      (PIM1 |=  (1<<PEVE1A) )     //!< An external event which can generate a capture from retrigger/fault block A generates an interrupt
#define psc1DisableExternalEventAInterrupt()     (PIM1 &= ~(1<<PEVE1A) )     //!< An external event which can generate a capture from retrigger/fault block A doesn't generate any interrupt

#define psc1EnableExternalEventBInterrupt()      (PIM1 |=  (1<<PEVE1B) )     //!< An external event which can generate a capture from retrigger/fault block B generates an interrupt
#define psc1DisableExternalEventBInterrupt()     (PIM1 &= ~(1<<PEVE1B) )     //!< An external event which can generate a capture from retrigger/fault block B doesn't generate any interrupt

#define psc1EnableEndOfCycleInterrupt()          (PIM1 |=  (1<<PEVE1A) )     //!< An interrupt is generated when PSC1 reaches the end of the whole cycle
#define psc1DisableEndOfCycleInterrupt()         (PIM1 &= ~(1<<PEVE1A) )     //!< No interrupt is generated when PSC1 reaches the end of the whole cycle
      //! @}

      //! @defgroup PSC1_interrupt_flag_control PSC1 Interrupt Flag Control
      //! PSC1 interrupt flag control
      //! @{
#define psc1IsSynchroErrorInterruptFlagSet()    (PIFR1 & (1<<PSEI0) )       //!< Return 1 if the PSEI0 bit in PIFR1 is set
#define psc1ClearSynchroErrorInterruptFlag()     (PIFR1 &= ~(1<<PSEI0) )     //!< Clear PSEI0 bit in PIFR1 register

#define psc1IsExternalEventAInterruptFlagSet() (PIFR1 & (1<<PEV0A) )       //!< Return 1 if the PEV0A bit in PIFR1 is set
#define psc1ClearExternalEventAInterruptFlag()  (PIFR1 &= ~(1<<PEV0A) )     //!< Clear PEV0A bit in PIFR1 register

#define psc1IsExternalEventBInterruptFlagSet() (PIFR1 & (1<<PEV0B) )       //!< Return 1 if the PEV0B bit in PIFR1 is set
#define psc1ClearExternalEventBInterruptFlag()  (PIFR1 &= ~(1<<PEV0B) )     //!< Clear PEV0B bit in PIFR1 register

#define psc1IsEndOfCycleInterruptFlagSet()     (PIFR1 & (1<<PEOP1) )       //!< Return 1 if the PEOP1 bit in PIFR1 is set
#define psc1ClearEndOfCycleInterruptFlag()      (PIFR1 &= ~(1<<PEOP1) )     //!< Clear PEOP1 bit in PIFR1 register
      //! @}
   //! @}


   //! @defgroup PSC2_macros PSC2 Macros
   //! PSC2 Macros
   //! @{

      //! @defgroup PSC2_output_configuration PSC2 Output Configuration
      //! Select the PSC2 Outputs
      //! @{
#define psc2Enable_out20()                             (PSOC2 |=  (1<<POEN2A) )  //!< Enable PSC2 Waveform Generator A
#define psc2Disable_out20()                            (PSOC2 &= ~(1<<POEN2A) )  //!< Disable PSC2 Waveform Generator A

#define psc2Enable_out21()                             (PSOC2 |=  (1<<POEN2B) )  //!< Enable PSC2 Waveform Generator B
#define psc2Disable_out21()                            (PSOC2 &= ~(1<<POEN2B) )  //!< Disable PSC2 Waveform Generator B
//! Enable Both PSC2 Waveform Generator A and B
#define psc2EnableBothOutputs()					(PSOC2 |=  ((1<<POEN2A) | (1<<POEN2B)))
//! Disable Both PSC2 Waveform Generator A and B
#define psc2DisableBothOutputs()				(PSOC2 &= ~((1<<POEN2A) | (1<<POEN2B)))

#define psc2OutputsActiveHigh()                    (PCNF2 |=  (1<<POP2) )    //!< PSC2 outputs are active low
#define psc2OutputsActiveLow()                     (PCNF2 &= ~(1<<POP2) )    //!< PSC2 outputs are active high
      //! @}

      //! @defgroup PSC2_mode_control_module PSC2 Mode Control
      //! PSC2 Mode Control
      //! @{
#define psc2EnableFiftyPercentMode()              (PCNF2 |=  (1<<PFIFTY2) )  //!< PSC2 is in 50% mode: Only OCR2RBH/L and OCR2SBH/L are used. They are duplicated in OCR2R/SAH/L during the update of OCR2BH/L
#define psc2DisableFiftyPercentMode()             (PCNF2 &= ~(1<<PFIFTY2) )  //!< OCR2R/SAH/L and OCR2R/SBH/L are fully independant

#define psc2EnableAutolockMode()                   (PCNF2 |=  (1<<PALOCK2) )  //!< OCR2R/SAH/L and OCR2R/SBH/L can be written without disturbing the PSC cycle. The update of these registers will be proceed at the end of the PSC cycle if the OCR2RB has been last written
#define psc2DisableAutolockMode()                  (PCNF2 &= ~(1<<PALOCK2) )  //!< The update will be procced according to PLOCK2 bit

#define psc2LockCompareValues()                    (PCNF2 |=  (1<<PLOCK2) )   //!< Take care that the lock is active only if you have disabled the autolock mode
#define psc2UpdateCompareValues()                  (PCNF2 &= ~(1<<PLOCK2) )   //!< The compare registers will be updated with the content of OCR2AH/L and OCR2BH
      //! @}

      //! @defgroup PSC2_clock_control PSC2 Clock Control
      //! PSC2 Clock Control
      //! @{

         //! @defgroup PSC2_clock_selection PSC2 Clock Selection
         //! PSC2 Clock Selection
         //! @{
//! Connect the PSC2 input clock to the PLL
#define psc2UsePllClock()                          (PCNF2 |= (1<<PCLKSEL0) )
//! Connect the PSC2 input clock to the I/O clock
#define psc2UseIoClock()                           (PCNF2 &= ~(1<<PCLKSEL0) )
//! Start the PLL at 64MHz and connect it to PSC2
#define psc2Use64megaPllClock()                                          \
          (Start_pll_64_mega(),                                               \
           Wait_pll_ready(),                                                  \
           Psc2_use_pll_clock() )
//! Start the PLL at 32MHz and connect it to PSC2
#define psc2Use32megaPllClock()                                          \
          (Start_pll_32_mega(),                                               \
           Wait_pll_ready(),                                                  \
           Psc2_use_pll_clock() )
         //! @}

         //! @defgroup PSC2_prescaler_control PSC2 Prescaler Control
         //! PSC2 Prescaler Control
         //! @{
//! No PSC2prescaler
#define psc2DisablePrescaler()			(PCTL2 &= ~(  (1<<PPRE21) | (1<<PPRE20) ) )
//! PSC2 clock is internally divided by 4
#define psc2DivideInputClockBy4()		(PCTL2 &= ~(1<<PPRE21),PCTL2 |=  (1<<PPRE20) )
//! PSC2 clock is internally divided by 32
#define psc2DivideInputClockBy32()		(PCTL2 |=  (1<<PPRE21),PCTL2 &= ~(1<<PPRE20) )
//! PSC2 clock is internally divided by 256
#define psc2DivideInputClockBy256()		(PCTL2 |=  ((1<<PPRE21) | (1<<PPRE20)) )
         //! @}

      //! @}

      //! @defgroup PSC2_ramp_mode_selection PSC2 Ramp Mode Selection
      //! PSC2 Ramp Mode Selection
      //! @{
      //! PSC2 is configured in one ramp mode, it means that the internal counter
      //! counts from 0 up to OCR2RB
#define psc2InOneRampMode()				(PCNF2 &= ~(  (1<<PMODE21) | (1<<PMODE20) ) )
//! PSC2 is configured in two ramp mode, it means that the internal counter
//! counts from 0 up to OCR2RA then from 0 to OCR2RB
#define psc2InTwoRampMode()				(PCNF2 &= ~(1<<PMODE21),PCNF2 |=  (1<<PMODE20) )
//! PSC2 is configured in for ramp mode, it means that the internal counter
//! counts from 0 up to OCR2SA then from 0 to OCR2RA then from 0 to OCR2SB then from 0 to OCR2RB
#define psc2InFourRampMode()			(PCNF2 |=  (1<<PMODE21),PCNF2 &= ~(1<<PMODE20) )
//! PSC2 is configured in for ramp mode, it means that the internal counter
//! counts from 0 up to OCR2RB then from OCR2RB downto 0
#define psc2InCenteredAlignedMode()		(PCNF2 |=  (  (1<<PMODE21) | (1<<PMODE20) ) )
      //! @}

      //! @defgroup PSC2_flank_width_modulation_configuration PSC2 Flank Width Modulation Configuration
      //! Select PSC2 Flank Width Modulation Configuration
      //! @{
#define psc2SymetricalFlankWidthModulation()      (PCTL2 |=  (1<<PBFM2) )     //!< PSC2 Flank width modulation operates on both OCR2RA and OCR2RB
#define psc2EndOfCycleFlankWidthModulation()    (PCTL2 &= ~(1<<PBFM2) )     //!< PSC2 Flank width modulation operates only on OCR2RB
      //! @}

      //! @defgroup PSC2_adc_amplifier_trigger_configuration PSC2 ADC Amplifier Trigger Configuration
      //! Select the PSC2 trigger configuration for the ADC or the amplifier
      //! @{
//! The PSC2 synchronization signal is sent to the ADC/Amplifier on waveform generator A leading edge
#define psc2SynchroOnWaveformGeneratorALeadingEdge()                   \
           (PSCO2  &= ~(  (1<<PSYNC21) | (1<<PSYNC20) ) )
//! The PSC2 synchronization signal is sent to the ADC/Amplifier on waveform generator A trailing edge
#define psc2SynchroOnWaveformGeneratorATrailingEdge()                  \
           (PSCO2 &= ~(1<<PSYNC21),                                           \
            PSCO2 |=  (1<<PSYNC20) )
//! The PSC2 synchronization signal is sent to the ADC/Amplifier on waveform generator B leading edge
#define psc2SynchroOnWaveformGeneratorBLeadingEdge()                   \
           (PSCO2 |=  (1<<PSYNC21),                                           \
            PSCO2 &= ~(1<<PSYNC20) )
//! The PSC2 synchronization signal is sent to the ADC/Amplifier on waveform generator B trailing edge
#define psc2SynchroOnWaveformGeneratorBTrailingEdge()                  \
           (PSCO2 |=  (  (1<<PSYNC21) | (1<<PSYNC20) ) )
      //! @}

      //! @defgroup PSC2_run_control PSC2 Run Control
      //! Turn On and Off the PSC2
      //! @{
#define psc2Start()                                  (PCTL2 |=  (1<<PRUN2) )     //!< Turn On PSC2
#define psc2Stop()                                   (PCTL2 &= ~(1<<PRUN2) )     //!< Turn Off PSC2
//! Turn Off PSC2 and the end of cycle
#define Psc2CompleteWaveformAndStop()             (PCTL2 |=  (1<<PCCYC2), \
                                                       PCTL2 &= ~(1<<PRUN2) )
#define psc2IsStarted()                             (PCTL2 & (1<<PRUN2) )
      //! @}

      //! @defgroup PSC2_fault_mode_configuration PSC2 Fault Mode Configuration
      //! PSC2 Fault Mode Configuration
      //! @{
#define psc2EnableFaultMode_out20()                  (PCTL2 |=  (1<<PAOC2A) )    //!< Fault input select to block A can act directly to PSCOUT00 output
#define psc2DisableFaultMode_out20()                 (PCTL2 &= ~(1<<PAOC2A) )    //!< No fault or retrigger management on PSCOUT00

#define psc2EnableFaultMode_out21()                  (PCTL2 |=  (1<<PAOC2B) )    //!< Fault input select to block A can act directly to PSCOUT00 output
#define psc2DisableFaultMode_out21()                 (PCTL2 &= ~(1<<PAOC2B) )    //!< No fault or retrigger management on PSCOUT01

#define psc2EnableAutorun()                         (PCTL2 |=  (1<<PARUN2) )    //!< Setting PRUN1 in PCTL1 register or setting both PARUN1 in PCTL1 register and PRUN0 in PCTL0 register will make the two PSC start simultaneously
#define psc2DisableAutorun()                        (PCTL2 &= ~(1<<PARUN2) )    //!< No synchronization between PSC2 and PSC2 exists
      //! @}

      //! @defgroup PSC2_interrupt_configuration PSC2 Interrupt Configuration
      //! PSC2 interrupt configuration
      //! @{
#define psc2EnableSynchroErrorInterrupt()         (PIM2 |=  (1<<PSEIE2) )     //!< An interrupt is generated when the PSEI0 bit is set
#define psc2DisableSynchroErrorInterrupt()        (PIM2 &= ~(1<<PSEIE2) )     //!< No interrupt is generated when the PSEI0 bit is set

#define psc2EnableExternalEventAInterrupt()      (PIM2 |=  (1<<PEVE2A) )     //!< An external event which can generate a capture from retrigger/fault block A generates an interrupt
#define psc2DisableExternalEventAInterrupt()     (PIM2 &= ~(1<<PEVE2A) )     //!< An external event which can generate a capture from retrigger/fault block A doesn't generate any interrupt

#define psc2EnableExternalEventBInterrupt()      (PIM2 |=  (1<<PEVE2B) )     //!< An external event which can generate a capture from retrigger/fault block B generates an interrupt
#define psc2DisableExternalEventBInterrupt()     (PIM2 &= ~(1<<PEVE2B) )     //!< An external event which can generate a capture from retrigger/fault block B doesn't generate any interrupt

#define psc2EnableEndOfCycleInterrupt()          (PIM2 |=  (1<<PEOPE2) )     //!< An interrupt is generated when PSC2 reaches the end of the whole cycle
#define psc2DisableEndOfCycleInterrupt()         (PIM2 &= ~(1<<PEOPE2) )     //!< No interrupt is generated when PSC2 reaches the end of the whole cycle
      //! @}

      //! @defgroup PSC2_interrupt_flag_control PSC2 Interrupt Flag Control
      //! PSC2 interrupt flag control
      //! @{
#define psc2IsSynchroErrorInterruptFlagSet()    	(PIFR2 & (1<<PSEI0) )       //!< Return 1 if the PSEI0 bit in PIFR2 is set
#define psc2ClearSynchroErrorInterruptFlag()    	 (PIFR2 &= ~(1<<PSEI0) )     //!< Clear PSEI0 bit in PIFR2 register

#define psc2IsExternalEventAInterruptFlagSet()	 (PIFR2 & (1<<PEV0A) )       //!< Return 1 if the PEV0A bit in PIFR2 is set
#define psc2ClearExternalEventAInterruptFlag()	  (PIFR2 &= ~(1<<PEV0A) )     //!< Clear PEV0A bit in PIFR2 register

#define psc2IsExternalEventBInterruptFlagSet()	 (PIFR2 & (1<<PEV0B) )       //!< Return 1 if the PEV0B bit in PIFR2 is set
#define psc2ClearExternalEventBInterruptFlag() 	 (PIFR2 &= ~(1<<PEV0B) )     //!< Clear PEV0B bit in PIFR2 register

#define psc2IsEndOfCycleInterruptFlagSet()     		(PIFR2 & (1<<PEOP2) )       //!< Return 1 if the PE2P2 bit in PIFR2 is set
#define psc2ClearEndOfCycleInterruptFlag()   	     (PIFR2 &= ~(1<<PEOP2) )     //!< Clear PEOP2 bit in PIFR2 register
      //! @}
   //! @}


//_____ D E F I N I T I O N S ______________________________________________
   //! @defgroup PSC_structure_definitions PSC Structure Definitions
   //! These definitions shall be used by the PSC functions
   //! @{
typedef struct stPscValues {
   uint16_t deadtime0;
   uint16_t ontime0;
   uint16_t deadtime1;
   uint16_t ontime1;
}PscValues;
   //! @}

//_____ F U N C T I O N S __________________________________________________
   //! @defgroup PSC0_low_level_functions PSC0 Low Level Fucntions
   //! This section allows to fully configure the PSC0 mode and to start it with the wanted Comparison values
   //! @{
//! Configures the PSC0 accordingly to the PSC0 Define Configuration values,
//! Then Init the PSC0 comparison values and start it
void psc0Init(void);
//! Update all the PSC0 comparison values accordingly to the four values
//! passed as uint16_t parameters
void psc0Update( PscValues *psc0Values );
   //! @}

   //! @defgroup PSC1_low_level_functions PSC1 Low Level Fucntions
   //! This section allows to fully configure the PSC1 mode and to start it with the wanted Comparison values
   //! @{
//! Configures the PSC1 accordingly to the PSC1 Define Configuration values,
//! Then Init the PSC1 comparison values and start it
void psc1Init(void);
//! Update all the PSC1 comparison values accordingly to the four values
//! passed as uint16_t parameters
void psc1Update( PscValues *psc1Values );
   //! @}

   //! @defgroup PSC2_low_level_functions PSC2 Low Level Fucntions
   //! This section allows to fully configure the PSC2 mode and to start it with the wanted Comparison values
   //! @{
//! Configures the PSC2 accordingly to the PSC2 Define Configuration values,
//! Then Init the PSC2 comparison values and start it
void psc2Init(void);
//! Update all the PSC2 comparison values accordingly to the four values
//! passed as uint16_t parameters
void psc2Update( PscValues *psc2Values );
   //! @}

void pscUpdateAll(PscValues *pscValues);

//! @}
#endif  // PSC_DRV_H
