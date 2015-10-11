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

#define SV_MAX_INVALID_PULSES 3
#define SV_NO_PULSE UINT16_MAX
#define SV_PULSE_MAX 10
#define SV_PULSE_MIN 1

static volatile uint8_t servo_invalidPulseCnt;
static volatile uint16_t servo_currentPulseWidth;
static volatile uint16_t servo_tmpCtrVal;
static volatile bool timer1Overflow;

void SVI_Init(void)
{
    servo_invalidPulseCnt = 0;
    servo_currentPulseWidth = 0;
    servo_tmpCtrVal = 0;
    timer1Overflow = false;
}

void SVI_Start(void)
{
    TMR1_EnableICP();
}

void SVI_Stop(void)
{
    TMR1_DisableICP();
}

uint16_t SVI_GetPulseWidth(void)
{
    return servo_currentPulseWidth;
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
                if (++servo_invalidPulseCnt > SV_MAX_INVALID_PULSES)
                {
                    servo_currentPulseWidth = SV_NO_PULSE;
                }
            }
            else
            {
                servo_currentPulseWidth = tmpVal;
                servo_invalidPulseCnt = 0;
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
        servo_currentPulseWidth = SV_NO_PULSE;
        servo_tmpCtrVal = 0;
        timer1Overflow = false;
    }
    else
    {
        timer1Overflow = true;
    }
}