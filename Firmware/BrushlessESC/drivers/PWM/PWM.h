/*!
***     \file	  PWM.c
***     \ingroup  PWM
***     \author   Daniel
***     \date	  9/20/2015 1:41:42 AM
***     \brief    TODO
***
******************************************************************************/

/* Header file guard symbol to prevent multiple includes */
#ifndef PWM_H_
#define PWM_H_

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
typedef enum PWM_Prescaler_e
{
	PWM_PRESCALER_1 = _BV(CS20),
	PWM_PRESCALER_8 = _BV(CS21),
	PWM_PRESCALER_32 = _BV(CS20|CS21),
	PWM_PRESCALER_64 = _BV(CS22),
	PWM_PRESCALER_128 = _BV(CS22|CS20),
	PWM_PRESCALER_256 = _BV(CS22|CS21),
	PWM_PRESCALER_1024 = _BV(CS22|CS21|CS20)
}PWM_Prescaler_t;

/*=============================================================================
=======                              EXPORTS                            =======
=============================================================================*/
void PWM_Init(void);
void PWM_Stop(void);
void PWM_Start(PWM_Prescaler_t prescaler);
void PWM_SetDutyMode(void);
void PWM_SetFrequencyMode(void);
void PWM_SetValue(uint8_t value);
/* end of storage class specifier if used with C++ */
#ifdef  __cplusplus
}
#endif

#endif /*PWM_H_*/
