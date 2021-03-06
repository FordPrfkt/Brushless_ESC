/*!
***     \file	  ACP.c
***     \ingroup  ACP
***     \author   Daniel
***     \date	  9/20/2015 3:53:04 AM
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
#include "ACP.h"
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
void ACP_Init(void)
{
	DIDR1 = _BV(AIN0D);
	ADCSRB = _BV(ACME);
	ACSR = _BV(ACD)|_BV(ACI)|_BV(ACIE)|_BV(ACIS1);
}

inline void ACP_Enable(void)
{
	ACSR &= ~_BV(ACD);
}

inline void ACP_Disable(void)
{
	ACSR |= _BV(ACD);	
}

inline void ACP_SelectInput(ACP_Input_t input)
{
	if ((ACSR & _BV(ACD)) == _BV(ACD))
	{
		ADMUX = (ADMUX & 0xE0) | input;		
	}
}
/* -----------------------------------------------------
 * --               Private functions                  --
 * ----------------------------------------------------- */

/* EOF */