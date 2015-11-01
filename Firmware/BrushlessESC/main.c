/*!
***     \file	  main.c
***     \ingroup  main
***     \author   Daniel
***     \date	  9/19/2015 12:38:27 PM
***     \brief    TODO
***
******************************************************************************/

/*=============================================================================
 =======                            INCLUDES                             =======
 =============================================================================*/
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/sfr_defs.h>
#include <avr/signature.h>
#include <avr/interrupt.h>
#include "drivers/ACP/ACP.h"
#include "drivers/ADC/ADC.h"
#include "drivers/Timer/Timer1.h"
#include "drivers/PWM/PWM.h"
#include "drivers/SPI/SPI_slave.h"
#include "ServoInput/ServoInput.h"
#include "LED/LED.h"
#include "BLDC/BLDC.h"
#include "MotorController.h"

/*=============================================================================
 =======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
 =============================================================================*/
/* Timer 0 einstellungen */
#define TIMER0_PRESCALER64() (_BV(CS00)|_BV(CS01))
#define TIMER0_1MS() (250) /* Timerwert für 1ms bei Prescaler 64. */

/*=============================================================================
 =======                       CONSTANTS  &  TYPES                       =======
 =============================================================================*/

/*=============================================================================
 =======                VARIABLES & MESSAGES & RESSOURCEN                =======
 =============================================================================*/
static volatile bool run1msTask = false;

/*=============================================================================
 =======                              METHODS                           =======
 =============================================================================*/

/* -----------------------------------------------------
 * --               Public functions                  --
 * ----------------------------------------------------- */
int main(void)
{
    ACP_Init();
	ADC_Init();
    ADC_SelectReference(ADC_REF_AVCC);
	PWM_Init();
	SPI_SlaveInit();
	TMR1_Init(0);
    LED_Init();
	SVI_Init();
    MC_Init();
    
    /* 1ms Timer0 starten */
    TCCR0A = 0;
    TCCR0B = TIMER0_PRESCALER64(); /* Prescaler 64 */
    OCR0B = TIMER0_1MS();
    TIMSK0 = _BV(OCIE0B);
    TCNT0 = 0;

    wdt_enable(WDTO_500MS);

	do 
	{
        if (true == run1msTask)
        {
            run1msTask = false;
        }
        
		BLDC_Mainfunction();
        MC_Cyclic_1ms();
        LED_Cyclic_1ms();
        
        wdt_reset();
	} while (1);
}
/* -----------------------------------------------------
 * --               Private functions                  --
 * ----------------------------------------------------- */

/* Timer 0 1ms Interrupt */
ISR(TIMER0_COMPB_vect, ISR_NOBLOCK)
{
    run1msTask = true;
    TIMSK0 = 0;
}

/* EOF */