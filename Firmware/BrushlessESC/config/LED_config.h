/*!
***     \file	  LED_config.c
***     \ingroup  LED_config
***     \author   Daniel
***     \date	  10/9/2015 12:15:48 AM
***     \brief    TODO
***
******************************************************************************/

/* Header file guard symbol to prevent multiple includes */
#ifndef LED_config_H_
#define LED_config_H_

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
/* LED Ausgang */
#define LED_DDR DDRC
#define LED_DDD DDD0
#define LED_PORT PORTC
#define LED_PIN PORTC0

/*=============================================================================
=======                       CONSTANTS  &  TYPES                       =======
=============================================================================*/

/*=============================================================================
=======                              EXPORTS                            =======
=============================================================================*/

/* end of storage class specifier if used with C++ */
#ifdef  __cplusplus
}
#endif

#endif /*LED_config_H_*/
/* EOF */