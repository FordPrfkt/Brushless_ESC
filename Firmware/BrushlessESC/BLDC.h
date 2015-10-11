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
#include <stdint.h>
#include <stdbool.h>

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
	BLDC_ERROR_OVERCURRENT,
	BLDC_ERROR_OVERVOLTAGE,
	BLDC_ERROR_UNDERVOLTAGE,
	BLDC_ERROR_NO_SIGNAL,
	BLDC_ERROR_WDG_RESET,
	BLDC_ERROR_BROWNOUT_RESET,
	BLDC_ERROR_NO_BEMF_A,
	BLDC_ERROR_NO_BEMF_B,
	BLDC_ERROR_NO_BEMF_C
}BLDC_Error_t;

typedef struct BLDC_Config_s
{
	uint16_t escID;
    uint16_t maxCurrent;
	uint16_t minVoltage;
	uint16_t maxVoltage;
	uint16_t motorConstant;
	uint16_t alignTime;
	uint8_t rampPwm1;
	uint8_t rampPwm2;
	uint8_t rampTime1;
	uint8_t rampTime2;
	uint8_t pwmMin;
	uint8_t pwmMax;
    uint8_t direction:1;
	uint8_t autoArm:1;	
	uint8_t beepOnStart:1;
	uint8_t beepOnError:1;
	uint8_t autoCurrentLimit:1;
}BLDC_Config_t;

typedef struct BLDC_ServoInputData_s
{
    uint16_t minGas;
    uint16_t maxGas;
    uint16_t idleGas;
}BLDC_ServoCalData_t;

typedef struct BLDC_Status_s
{
	uint16_t motorCurrent;
	uint16_t batVoltage;
	uint16_t RPMActual;
	BLDC_State_t curState;
	BLDC_Error_t error;
}BLDC_Status_t;
/*=============================================================================
=======                              EXPORTS                            =======
=============================================================================*/
extern uint8_t bldc_PWMValue;
extern uint16_t bldc_RPMSetpopint;
extern volatile BLDC_Status_t bldc_Status;

void BLDC_Init(void);
void BLDC_Start(void);
void BLDC_StartMotor(void);
void BLDC_StopMotor(bool quickstop);
void BLDC_Mainfunction(void);

/* end of storage class specifier if used with C++ */
#ifdef  __cplusplus
}
#endif

#endif /*BLDC_H_*/
