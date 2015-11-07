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
#define TMR1_CPU_FREQ_MHZ (F_CPU / 1000000UL)
#define TMR1_TICK_DURATION_NS (10000UL / TMR1_CPU_FREQ_MHZ)

/*=============================================================================
 =======                       CONSTANTS  &  TYPES                       =======
 =============================================================================*/

/*=============================================================================
 =======                VARIABLES & MESSAGES & RESSOURCEN                =======
 =============================================================================*/
uint32_t tickDuration_ns_prescaled = 0;
/*=============================================================================
 =======                              METHODS                           =======
 =============================================================================*/

/* -----------------------------------------------------
 * --               Public functions                  --
 * ----------------------------------------------------- */
void TMR1_Init(TMR1_Prescaler_t prescaler)
{
    TIMSK1 = 0;
    TCCR1A = 0;
    TCCR1C = 0;
    TCCR1B = _BV(ICNC1)|_BV(ICES1)|prescaler;
    ICP1_DDR &= ~_BV(ICP1_BIT);    
    
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        switch(prescaler)
        {
            case TMR1_PRESCALER_1:
            tickDuration_ns_prescaled = TMR1_TICK_DURATION_NS;
            break;
        
            case TMR1_PRESCALER_8:
            tickDuration_ns_prescaled = TMR1_TICK_DURATION_NS * 8UL;
            break;
        
            case TMR1_PRESCALER_32:
            tickDuration_ns_prescaled = TMR1_TICK_DURATION_NS * 32UL;
            break;
        
            case TMR1_PRESCALER_64:
            tickDuration_ns_prescaled = TMR1_TICK_DURATION_NS * 64UL;
            break;
        
            case TMR1_PRESCALER_128:
            tickDuration_ns_prescaled = TMR1_TICK_DURATION_NS * 128UL;
            break;
        
            case TMR1_PRESCALER_256:
            tickDuration_ns_prescaled = TMR1_TICK_DURATION_NS * 256UL;
            break;
        
            case TMR1_PRESCALER_1024:
            tickDuration_ns_prescaled = TMR1_TICK_DURATION_NS * 1024UL;
            break;
        
            default:
            tickDuration_ns_prescaled = 0;
            break;
        }
    }    
}

inline void TMR1_EnableTimerA(uint16_t timerVal)
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

inline void TMR1_DisableTimerA(void)
{
    /* Interrupt deaktivieren */
    TIMSK1 &= ~_BV(OCIE1A);
}

inline void TMR1_EnableTimerB(uint16_t timerVal)
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

inline void TMR1_DisableTimerB(void)
{
    /* Interrupt deaktivieren */
    TIMSK1 &= ~_BV(OCIE1B);
}

inline uint16_t TMR1_GetTimerValue(void)
{
    uint16_t result;
    
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        result = TCNT1;
    }
    
    return result;
}

inline void TMR1_EnableICP(void)
{
    TIFR1 |= _BV(ICF1);
    TIMSK1 |= _BV(ICIE1);    
}

inline void TMR1_DisableICP(void)
{
    TIMSK1 &= ~_BV(ICIE1);    
}

uint32_t TMR1_Ticks2us(uint32_t ticks)
{
    uint32_t result;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        result = ticks * (tickDuration_ns_prescaled + 5555UL);
        result /= 10000UL;
    }
    return result;
}

uint32_t TMR1_us2Ticks(uint16_t us)
{
    uint32_t result;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        result = (us * 10000UL) / tickDuration_ns_prescaled;
    }
    
    return result;
}

uint32_t TMR1_Ticks2ns(uint32_t ticks)
{
    uint32_t result;
    
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        result = ticks * ((tickDuration_ns_prescaled + 5) / 10UL);
    }    
    
    return result;
}

uint32_t TMR1_ns2Ticks(uint32_t ns)
{
    uint32_t result;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        result = (ns * 10) / tickDuration_ns_prescaled;
    }
    
    return result;
}

/* EOF */