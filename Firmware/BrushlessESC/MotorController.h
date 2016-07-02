/*!
***     \file	  MotorController.c
***     \ingroup  MotorController
***     \author   Daniel
***     \date	  10/18/2015 12:53:20 AM
***     \brief    TODO
***
******************************************************************************/

/* Header file guard symbol to prevent multiple includes */
#ifndef MotorController_H_
#define MotorController_H_

/* storage class specifier if used with C++ */
#ifdef  __cplusplus
  extern "C" {
#endif

/*=============================================================================
=======                            INCLUDES                             =======
=============================================================================*/
#include "config/MotorController_config.h"
/*=============================================================================
=======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
=============================================================================*/

/*=============================================================================
=======                       CONSTANTS  &  TYPES                       =======
=============================================================================*/
typedef enum MC_State_e
{
    MC_STATE_STARTUP = 0,
    MC_STATE_DISARMED,
    MC_STATE_CHECK_THROTTLE,
    MC_STATE_CALIBRATE_MAX,
    MC_STATE_CALIBRATE_MIN,
    MC_STATE_ARMED,
    MC_STATE_RUNNING,
    MC_STATE_ERROR
}MC_State_t;

typedef enum MC_Error_e
{
    MC_NO_ERROR = 0,
	MC_ERROR_NO_SIGNAL = MC_ERROR_ID,
	MC_ERROR_WDG_RESET = MC_ERROR_ID + 1,
	MC_ERROR_BROWNOUT_RESET = MC_ERROR_ID + 2,
    MC_ERROR_ARMING_TIMEOUT = MC_ERROR_ID + 3,
    MC_ERROR_CAL_TIMEOUT = MC_ERROR_ID + 4,
    MC_ERROR_INTERNAL = MC_ERROR_ID + 5
}MC_Error_t;
/*=============================================================================
=======                              EXPORTS                            =======
=============================================================================*/
void MC_Init(void);
void MC_Cyclic_1ms(void);
void MC_SetThrottleValue_TWI(uint8_t throttleInput);
void MC_ArmTWI(void);
bool MC_GetArmed(void);
uint8_t MC_GetThrottle(void);
void MC_GetErrorMemory(uint8_t errorMem[], uint8_t *lastError);

/* end of storage class specifier if used with C++ */
#ifdef  __cplusplus
}
#endif

#endif /*MotorController_H_*/
/* EOF */