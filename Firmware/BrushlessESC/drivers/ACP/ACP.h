/*!
***     \file	  ACP.c
***     \ingroup  ACP
***     \author   Daniel
***     \date	  9/20/2015 3:53:14 AM
***     \brief    TODO
***
******************************************************************************/

/* Header file guard symbol to prevent multiple includes */
#ifndef ACP_H_
#define ACP_H_

/* storage class specifier if used with C++ */
#ifdef  __cplusplus
  extern "C" {
#endif

/*=============================================================================
=======                            INCLUDES                             =======
=============================================================================*/
#include <avr/io.h>
#include <avr/sfr_defs.h>

/*=============================================================================
=======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
=============================================================================*/
typedef enum ACP_Input_e
{
	ACP_INPUT_AIN1 = _BV(MUX0),
	ACP_INPUT_ADC1 = _BV(MUX1),
	ACP_INPUT_ADC2 = _BV(MUX2),
	ACP_INPUT_ADC3 = _BV(MUX1)|_BV(MUX2),
	ACP_INPUT_ADC4 = _BV(MUX3),
	ACP_INPUT_ADC5 = _BV(MUX3)|_BV(MUX1),
	ACP_INPUT_ADC6 = _BV(MUX3)|_BV(MUX2),
	ACP_INPUT_ADC7 = _BV(MUX1)|_BV(MUX2)|_BV(MUX3)
}ACP_Input_t;
/*=============================================================================
=======                       CONSTANTS  &  TYPES                       =======
=============================================================================*/

/*=============================================================================
=======                              EXPORTS                            =======
=============================================================================*/
void ACP_Init(void);
void ACP_Enable(void);
void ACP_Disable(void);
void ACP_SelectInput(ACP_Input_t input);

/* end of storage class specifier if used with C++ */
#ifdef  __cplusplus
}
#endif

#endif /*ACP_H_*/
/* EOF */