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

/*=============================================================================
=======                              EXPORTS                            =======
=============================================================================*/
void MC_Init(void);
void MC_Cyclic_1ms(void);
void MC_SetThrottleValue_SPI(uint8_t throttleInput);
void MC_ArmSPI(void);
uint8_t MC_GetThrottle(void);

/* end of storage class specifier if used with C++ */
#ifdef  __cplusplus
}
#endif

#endif /*MotorController_H_*/
