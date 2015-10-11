/*!
***     \file	  LED.c
***     \ingroup  LED
***     \author   Daniel
***     \date	  10/8/2015 11:50:24 PM
***     \brief    TODO
***
******************************************************************************/

/* Header file guard symbol to prevent multiple includes */
#ifndef LED_H_
#define LED_H_

/* storage class specifier if used with C++ */
#ifdef  __cplusplus
  extern "C" {
#endif

/*=============================================================================
=======                            INCLUDES                             =======
=============================================================================*/

/*=============================================================================
=======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
=============================================================================*/

/*=============================================================================
=======                       CONSTANTS  &  TYPES                       =======
=============================================================================*/

/*=============================================================================
=======                              EXPORTS                            =======
=============================================================================*/
void LED_Init(void);
void LED_Cyclic_1ms(void);
void LED_On(void);
void LED_Off(void);
void LED_Blink(uint16_t interval);
void SIG_Beep(uint16_t freq, uint16_t duration);

/* end of storage class specifier if used with C++ */
#ifdef  __cplusplus
}
#endif

#endif /*LED_H_*/
