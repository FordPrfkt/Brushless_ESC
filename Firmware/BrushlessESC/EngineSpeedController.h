/*!
***     \file	  SpeedController.c
***     \ingroup  SpeedController
***     \author   Daniel
***     \date	  9/19/2015 12:40:19 PM
***     \brief    TODO
***
******************************************************************************/

/* Header file guard symbol to prevent multiple includes */
#ifndef SpeedController_H_
#define SpeedController_H_

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

#endif /*SpeedController_H_*/
