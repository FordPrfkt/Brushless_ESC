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
#include <stdint.h>
#include <stdbool.h>
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
ADC_Reference_t adc_currentRef;
bool adc_RefChanged;

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
    
    adc_currentRef = ADC_REF_AVCC;
    adc_RefChanged = false;
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
    if (adcRef != adc_currentRef)
    {
        adc_currentRef = adcRef;
        adc_RefChanged = true;
    }
    
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
ISR(ADC_vect)
{
    uint16_t result;

    if (true == adc_RefChanged)
    {
        /* Das erste Ergebnis nach dem Umschalten der Referenz sollte verworfen werden weil ungenau */
        ADC_StartConversion();
    }
    else
    {
        /* Handler aufrufen */
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            result = ADC;
        }
        ADC_ConversionCallback(result);
    }
}
/* EOF */