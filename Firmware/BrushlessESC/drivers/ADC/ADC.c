/*!
***     \file	  ADC.c
***     \ingroup  ADC
***     \author   Daniel
***     \date	  9/20/2015 5:55:57 PM
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
#include "ADC.h"
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
void ADC_Init(void)
{
	ADCSRA = _BV(ADIE)|_BV(ADPS0);
	ADCSRB = 0;
	DIDR0 = _BV(ADC0D)|_BV(ADC1D)|_BV(ADC2D)|_BV(ADC3D)|_BV(ADC4D)|_BV(ADC5D);
	ADMUX = 0;
}

inline void ADC_Enable(void)
{
	ADCSRA |= _BV(ADEN);
}

inline void ADC_Disable(void)
{
	ADCSRA &= ~_BV(ADEN);
}

inline void ADC_SelectInput(ADC_Input_t input)
{
	ADMUX = (ADMUX & 0xE0) | input;
}

void ADC_SelectReference(ADC_Reference_t adcRef)
{
    ADMUX = (ADMUX & 0x2F) | adcRef;
}

inline ADC_Input_t ADC_GetSelectedInput(void)
{
    return (ADMUX & 0xE0);
}

inline void ADC_StartConversion(void)
{
	ADCSRA |= _BV(ADSC);
}

inline uint16_t ADC_GetConversionResult(void)
{
    uint16_t result;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        result = ADC;
    }
    
    return result;
}
/* -----------------------------------------------------
 * --               Private functions                  --
 * ----------------------------------------------------- */

/* EOF */