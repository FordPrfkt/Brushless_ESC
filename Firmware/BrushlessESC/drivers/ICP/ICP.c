/*!
***     \file	  ICP.c
***     \ingroup  ICP
***     \author   Daniel
***     \date	  9/20/2015 2:42:03 AM
***     \brief    TODO
***
******************************************************************************/

/*=============================================================================
 =======                            INCLUDES                             =======
 =============================================================================*/
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "ICP.h"
/*=============================================================================
 =======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
 =============================================================================*/

/*=============================================================================
 =======                       CONSTANTS  &  TYPES                       =======
 =============================================================================*/

/*=============================================================================
 =======                VARIABLES & MESSAGES & RESSOURCEN                =======
 =============================================================================*/
static volatile uint16_t icp_currentDuty = 0;
static volatile uint16_t icp_tmpCtrVal = 0;
/*=============================================================================
 =======                              METHODS                           =======
 =============================================================================*/

/* -----------------------------------------------------
 * --               Public functions                  --
 * ----------------------------------------------------- */
void ICP_Init(void)
{
	TIMSK1 = 0;
	TCCR1A = 0;
	TCCR1C = 0;
	TCCR1B = _BV(ICNC1)|_BV(ICES1)|_BV(CS11);
	ICP1_DDR &= ~_BV(ICP1_BIT);
}

void ICP_Start(void)
{
	TIFR1 |= _BV(ICF1);
	TIMSK1 |= _BV(ICIE1);
}

void ICP_Stop(void)
{
	TIMSK1 &= ~_BV(ICIE1);
}

uint16_t ICP_GetValue(void)
{
	return icp_currentDuty;
}

/* -----------------------------------------------------
 * --               Private functions                  --
 * ----------------------------------------------------- */

ISR(TIMER1_CAPT_vect)
{
	uint16_t tmpVal;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		tmpVal = ICR1;
		TCCR1B ^= _BV(ICES1);
		TIFR1 |= _BV(ICF1);
		icp_currentDuty = tmpVal - icp_tmpCtrVal;
		icp_tmpCtrVal = tmpVal;
	}
}