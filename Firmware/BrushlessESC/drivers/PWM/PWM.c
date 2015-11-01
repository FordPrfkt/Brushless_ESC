/*!
***     \file	  PWM.c
***     \ingroup  PWM
***     \author   Daniel
***     \date	  9/20/2015 1:41:33 AM
***     \brief    TODO
***
******************************************************************************/

/*=============================================================================
 =======                            INCLUDES                             =======
 =============================================================================*/
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include "PWM.h"
/*=============================================================================
 =======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
 =============================================================================*/

/*=============================================================================
 =======                       CONSTANTS  &  TYPES                       =======
 =============================================================================*/

/*=============================================================================
 =======                VARIABLES & MESSAGES & RESSOURCEN                =======
 =============================================================================*/

/*=============================================================================
 =======                              METHODS                           =======
 =============================================================================*/

/* -----------------------------------------------------
 * --               Public functions                  --
 * ----------------------------------------------------- */
void PWM_Init(void)
{
	/* Clear OC2B on compare match when up-counting
	Set OC2B on compare match when down-counting
	
	Phase correct PWM
	
	No prescaler
	*/
	OCR2A = 0;
	TCNT2 = 0;
	TCCR2A = _BV(COM2B1)|_BV(WGM20);
	TCCR2B = _BV(WGM22);
	
	/* OC2B als Ausgang */
	OC2B_DDR |= _BV(OC2B_BIT);
}

inline void PWM_Stop(void)
{
	TCCR2B &= ~_BV(CS20)|_BV(CS21)|_BV(CS22);
}

inline void PWM_Start(PWM_Prescaler_t prescaler)
{
	TCCR2B &= ~_BV(CS20)|_BV(CS21)|_BV(CS22);
	TCCR2B |= prescaler;
}

inline void PWM_SetDutyMode(void)
{
	TCCR2A = _BV(COM2B1)|_BV(WGM20);
}

inline void PWM_SetFrequencyMode(void)
{
	TCCR2A = _BV(COM2B0)|_BV(COM2B1)|_BV(WGM20)|_BV(WGM21);
}

inline void PWM_SetValue(uint8_t value)
{
	OCR2A = value;
}

/* -----------------------------------------------------
 * --               Private functions                  --
 * ----------------------------------------------------- */

/* EOF */