/*!
***     \file	  BLDC.h
***     \ingroup  BLDC
***     \author   Daniel
***     \date	  9/19/2015 12:40:19 PM
***     \brief    TODO
***
******************************************************************************/

/* Header file guard symbol to prevent multiple includes */
#ifndef BLDC_H_
#define BLDC_H_

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
typedef enum BLDC_Direction_e
{
	BLDC_DIR_CW = 0,
	BLDC_DIR_CCW
}BLDC_Direction_t;

typedef enum BLDC_State_e
{
	BLDC_STATE_STOP = 0,
	BLDC_STATE_ALIGN,
	BLDC_STATE_RAMP_UP,
	BLDC_STATE_LAST_RAMP_UP,
	BLDC_STATE_RUNNING
}BLDC_State_t;

typedef enum BLDC_Error_e
{
	BLDC_NO_ERROR = 0,
	BLDC_ERROR_OVERCURRENT = 1,
	BLDC_ERROR_OVERVOLTAGE = 2,
	BLDC_ERROR_UNDERVOLTAGE = 4,
	BLDC_ERROR_NO_SIGNAL = 8,
	BLDC_ERROR_CPU_RESET = 16,
	BLDC_ERROR_NO_BEMF_A = 32,
	BLDC_ERROR_NO_BEMF_B = 64,
	BLDC_ERROR_NO_BEMF_C = 128
}BLDC_Error_t;
/*=============================================================================
=======                              EXPORTS                            =======
=============================================================================*/
void BLDC_Init(void);
void BLDC_Start(void);
void BLDC_StartMotor(void);
void BLDC_StopMotor(void);
void BLDC_StateMachine(void);

/* end of storage class specifier if used with C++ */
#ifdef  __cplusplus
}
#endif

#endif /*BLDC_H_*/
