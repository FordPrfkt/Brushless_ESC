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
#include "../config/BLDC_config.h"

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

typedef enum BLDC_LimitMode_e
{
    BLDC_NO_LIMIT = 0,    
    BLDC_LIMIT_SOFT = 1,
    BLDC_LIMIT_HARD = 2
}BLDC_LimitMode_t;

typedef enum BLDC_Error_e
{
	BLDC_NO_ERROR = 0,
	BLDC_ERROR_OVERCURRENT = BLDC_ERROR_ID,
	BLDC_ERROR_OVERVOLTAGE = BLDC_ERROR_ID + 1,
	BLDC_ERROR_UNDERVOLTAGE = BLDC_ERROR_ID + 2,
	BLDC_ERROR_NO_BEMF_A = BLDC_ERROR_ID + 3,
	BLDC_ERROR_NO_BEMF_B = BLDC_ERROR_ID + 4,
	BLDC_ERROR_NO_BEMF_C = BLDC_ERROR_ID + 5,
    BLDC_ERROR_MODE = BLDC_ERROR_ID + 6
}BLDC_Error_t;

typedef enum BLDC_State_e
{
    BLDC_STATE_STOP = 0,
    BLDC_STATE_TEST_TURNING,
    BLDC_STATE_ALIGN,
    BLDC_STATE_RAMP_UP,
    BLDC_STATE_LAST_RAMP_UP,
    BLDC_STATE_RUNNING
}BLDC_State_t;

typedef struct BLDC_Config_s
{
    uint16_t maxCurrent;
	uint16_t minVoltage;
	uint16_t maxVoltage;
	uint16_t alignTime;
	uint8_t rampPwm1;
	uint8_t rampPwm2;
	uint8_t rampTime1;
	uint8_t rampTime2;
    BLDC_Direction_t direction;
    BLDC_LimitMode_t currentLimitMode;
    BLDC_LimitMode_t voltageLimitMode;
}BLDC_Config_t;

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
void BLDC_Init(BLDC_Config_t *config_p);
void BLDC_Beep(uint16_t freqency, uint16_t duration);
void BLDC_SetPower(uint8_t power);
void BLDC_StartMotor(void);
void BLDC_StopMotor(bool quickstop);
volatile BLDC_Status_t* BLDC_GetStatus(void);
BLDC_Config_t* BLDC_GetConfig(void);
void BLDC_Mainfunction(void);

/* end of storage class specifier if used with C++ */
#ifdef  __cplusplus
}
#endif

#endif /*BLDC_H_*/
