/*!
***     \file	  LED.c
***     \ingroup  LED
***     \author   Daniel
***     \date	  10/8/2015 11:50:16 PM
***     \brief    TODO
***
******************************************************************************/

/*=============================================================================
 =======                            INCLUDES                             =======
 =============================================================================*/
#include <stdint.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include "LED_config.h"
#include "LED.h"

/*=============================================================================
 =======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
 =============================================================================*/
#define LED_ON() (LED_PORT |= _BV(LED_PIN))
#define LED_OFF() (LED_PORT &= ~_BV(LED_PIN))
#define LED_TOGGLE() (LED_PORT ^= _BV(LED_PIN))

/*=============================================================================
 =======                       CONSTANTS  &  TYPES                       =======
 =============================================================================*/

/*=============================================================================
 =======                VARIABLES & MESSAGES & RESSOURCEN                =======
 =============================================================================*/
uint16_t led_counter;
uint16_t led_interval;

/*=============================================================================
 =======                              METHODS                           =======
 =============================================================================*/

/* -----------------------------------------------------
 * --               Public functions                  --
 * ----------------------------------------------------- */
void LED_Init(void)
{
    led_interval = 0;
    led_counter = 0;    
    LED_DDR |= LED_DDD;
    LED_PORT &= ~_BV(LED_PIN);
    LED_OFF();
}

void LED_Cyclic_1ms(void)
{
    if (led_interval > 0)
    {
        if (++led_counter >= led_interval)
        {
            LED_TOGGLE();
            led_counter = 0;
        }
    }
}

void LED_On(void)
{
    led_interval = 0;
    LED_ON();
}
void LED_Off(void)
{
    led_interval = 0;
    LED_OFF();
}

void LED_Blink(uint16_t interval)
{
    led_counter = 0;
    led_interval = interval;
    LED_OFF();
}

/* -----------------------------------------------------
 * --               Private functions                  --
 * ----------------------------------------------------- */
