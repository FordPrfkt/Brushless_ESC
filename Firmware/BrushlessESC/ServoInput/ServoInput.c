/*
 * Servo_Input.c
 *
 * Created: 07.10.2015 01:22:18
 *  Author: Daniel
 */ 
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "../Drivers/Timer/Timer1.h"
#include "ServoInput.h"

static volatile uint8_t servo_invalidPulseCnt;
static volatile uint16_t servo_currentPulseDuration;
static volatile uint16_t servo_tmpCtrVal;
static volatile bool timer1Overflow;

static MAVG_FilterData_t bldc_PPMFilterData;
static MAVG_FilterContent_t bldc_PPMFilter[8];

void SVI_Init(void)
{
    servo_invalidPulseCnt = 0;
    servo_currentPulseDuration = 0;
    servo_tmpCtrVal = 0;
    timer1Overflow = false;
    MAVG_Init(&mc_PPMFilterData, 3, 0);
}

void SVI_Start(void)
{
    TMR1_EnableICP();
}

void SVI_Stop(void)
{
    TMR1_DisableICP();
}

uint16_t SVI_GetPulseDuration(void)
{
    if (false == signalError)
    {
        return MAVG_GetResult(&bldc_PPMFilterData);        
    }
    else
    {
        return SV_NO_PULSE;
    }
}

/* -----------------------------------------------------
 * --               Private functions                  --
 * ----------------------------------------------------- */
ISR(TIMER1_CAPT_vect, ISR_NOBLOCK)
{
	uint16_t tmpVal;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		tmpVal = ICR1;
		TCCR1B ^= _BV(ICES1);
		TIFR1 |= _BV(ICF1);
		
		if (0 == (TCCR1B & _BV(ICES1)))
		{
			/* Edge select ist jetzt falled, d.h. interrupt wurde von einer steigenden Flanke ausgelöst.
			Timerwert speichern. */
			servo_tmpCtrVal = tmpVal;
		}
		else
		{
			/* Edge select ist jetzt steigend, d.h. interrupt wurde von einer fallenden Flanke ausgelöst.
			Pulsdauer berechnen. */
            tmpVal -= servo_tmpCtrVal;

            if ((SV_PULSE_MAX < tmpVal) || (SV_PULSE_MIN > tmpVal))
            {
                if (false == signalError)
                {
                    if (++servo_invalidPulseCnt > SV_MAX_INVALID_PULSES)
                    {
                        signalError = true;
                    }                    
                }
            }
            else
            {
                if (true == signalError)
                {
                    if (--servo_invalidPulseCnt == 0)
                    {
                        signalError = false;
                        MAVG_Init(&bldc_PPMFilterData,3,tmpVal);                        
                    }
                }
                else
                {
                    MAVG_AddValue(&bldc_PPMFilterData, tmpVal);                    
                }
            }

            timer1Overflow = false;
		}
	}
}

ISR(TIMER1_OVF_vect)
{
    if (true == timer1Overflow)
    {
        TCCR1B |= _BV(ICES1);
        if (false == signalError)
        {
            servo_invalidPulseCnt += 3; /* 3*65535µs = 196ms */
            if (servo_invalidPulseCnt >= SV_MAX_INVALID_PULSES)
            {
                signalError = true;
            }
        }

        servo_tmpCtrVal = 0;
        timer1Overflow = false;
    }
    else
    {
        timer1Overflow = true;
    }
}