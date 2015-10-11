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
#include "Timer1.h"
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
void TMR1_Init(uint8_t prescaler)
{
    TIMSK1 = 0;
    TCCR1A = 0;
    TCCR1C = 0;
    TCCR1B = _BV(ICNC1)|_BV(ICES1)|_BV(CS11);
    ICP1_DDR &= ~_BV(ICP1_BIT);    
}

void TMR1_EnableTimerA(uint16_t timerVal)
{
    uint16_t temp = 0;
    
    /* timerVal auf aktuellen Timerwert addieren und
    interrupt aktivieren */
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        temp = TCNT1;
        temp += timerVal;
        OCR1A = temp;
    }
    TIMSK1 |= _BV(OCIE1A);
}

void TMR1_DisableTimerA(void)
{
    /* Interrupt deaktivieren */
    TIMSK1 &= ~_BV(OCIE1A);
}

void TMR1_EnableTimerB(uint16_t timerVal)
{
    uint16_t temp;

    /* timerVal auf aktuellen Timerwert addieren und
    interrupt aktivieren */
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        temp = TCNT1;
        temp += timerVal;
        OCR1B = temp;
    }
    TIMSK1 |= _BV(OCIE1B);
}

void TMR1_DisableTimerB(void)
{
    /* Interrupt deaktivieren */
    TIMSK1 &= ~_BV(OCIE1B);
}

uint16_t TMR1_GetTimerValue(void)
{
    uint16_t result;
    
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        result = TCNT1;
    }
    
    return result;
}

void TMR1_EnableICP(void)
{
    TIFR1 |= _BV(ICF1);
    TIMSK1 |= _BV(ICIE1);    
}

void TMR1_DisableICP(void)
{
    TIMSK1 &= ~_BV(ICIE1);    
}
