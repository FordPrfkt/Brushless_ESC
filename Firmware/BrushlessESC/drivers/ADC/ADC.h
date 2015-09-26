/*!
***     \file	  ADC.c
***     \ingroup  ADC
***     \author   Daniel
***     \date	  9/20/2015 5:56:05 PM
***     \brief    TODO
***
******************************************************************************/

/* Header file guard symbol to prevent multiple includes */
#ifndef ADC_H_
#define ADC_H_

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
typedef enum ADC_Input_e
{
	ADC_INPUT_ADC1 = _BV(MUX1),
	ADC_INPUT_ADC2 = _BV(MUX2),
	ADC_INPUT_ADC3 = _BV(MUX1)|_BV(MUX2),
	ADC_INPUT_ADC4 = _BV(MUX3),
	ADC_INPUT_ADC5 = _BV(MUX3)|_BV(MUX1),
	ADC_INPUT_ADC6 = _BV(MUX3)|_BV(MUX2),
	ADC_INPUT_ADC7 = _BV(MUX1)|_BV(MUX2)|_BV(MUX3)
}ADC_Input_t;

/*=============================================================================
=======                              EXPORTS                            =======
=============================================================================*/
void ADC_Init(void);
void ADC_Enable(void);
void ADC_Disable(void);
void ADC_SelectInput(ADC_Input_t input);
void ADC_StartConversion(void);

/* end of storage class specifier if used with C++ */
#ifdef  __cplusplus
}
#endif

#endif /*ADC_H_*/
