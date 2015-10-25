/*!
***     \file	  MotorController_config.c
***     \ingroup  MotorController_config
***     \author   Daniel
***     \date	  10/18/2015 11:02:58 PM
***     \brief    TODO
***
******************************************************************************/

/* Header file guard symbol to prevent multiple includes */
#ifndef MotorController_config_H_
#define MotorController_config_H_

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
#define MC_MIN_PULSE_DURATION (750) /* Min. Pulsdauer in µs */
#define MC_MAX_PULSE_DURATION (2250) /* Max. Pulsdauer in µs */
#define MC_THROTTLE_CAL_MAX_JITTER (10)
#define MC_CHECK_CAL_TIME (1000)
#define MC_ARMING_TIMEOUT (10000)
#define MC_CALIBRATE_TIME (2000)
#define MC_CALIBRATION_TIMEOUT (10000)

#define MC_PWM_STEPS (255)
#define MC_LOOP_INTERVAL (1)

/*=============================================================================
=======                       CONSTANTS  &  TYPES                       =======
=============================================================================*/
typedef struct MC_Config_s 
{
    uint16_t throttleOffDuration;
    uint16_t throttleFullDuration;
    uint16_t checkThrottleTime;
    uint16_t throttleTimeout;
    uint8_t minThrottle;
    uint8_t maxThrottle;
}MC_Config_t;

/*=============================================================================
=======                              EXPORTS                            =======
=============================================================================*/
extern MC_Config_t MC_ConfigDataEE; 
extern BLDC_Error_t MC_ErrorMemoryEE[];
extern uint8_t MC_LastErrorEE;
extern BLDC_Config_t MC_bldcConfigDataEE;

/* end of storage class specifier if used with C++ */
#ifdef  __cplusplus
}
#endif

#endif /*MotorController_config_H_*/
