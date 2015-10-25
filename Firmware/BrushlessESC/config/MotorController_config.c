/*!
***     \file	  MotorControllerConfig.c
***     \ingroup  MotorControllerConfig
***     \author   Daniel
***     \date	  25.10.2015 00:11:46
***     \brief    TODO
***
******************************************************************************/

/*=============================================================================
 =======                            INCLUDES                             =======
 =============================================================================*/
#include <stdint.h>
#include <stdbool.h>
#include <avr/eeprom.h>
#include "../BLDC/BLDC.h"
#include "MotorController_config.h"
/*=============================================================================
 =======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
 =============================================================================*/

/*=============================================================================
 =======                       CONSTANTS  &  TYPES                       =======
 =============================================================================*/

/*=============================================================================
 =======                VARIABLES & MESSAGES & RESSOURCEN                =======
 =============================================================================*/
MC_Config_t MC_ConfigDataEE EEMEM = 
{
    .throttleOffDuration = 1060,
    .throttleFullDuration = 1860,
    .checkThrottleTime = 1000, 
    .throttleTimeout = 250,
};

BLDC_Error_t MC_ErrorMemoryEE[10] EEMEM =
{
    BLDC_NO_ERROR,
    BLDC_NO_ERROR,
    BLDC_NO_ERROR,
    BLDC_NO_ERROR,
    BLDC_NO_ERROR,
    BLDC_NO_ERROR,
    BLDC_NO_ERROR,
    BLDC_NO_ERROR,
    BLDC_NO_ERROR,
    BLDC_NO_ERROR
};

uint8_t MC_LastErrorEE EEMEM = 0;

BLDC_Config_t MC_bldcConfigDataEE EEMEM =
{
    .maxCurrent = 1,
    .minVoltage = 1,
    .maxVoltage = 1,
    .alignTime = 1000,
    .rampPwm1 = 10,
    .rampPwm2 = 60,
    .rampTime1 = 10,
    .rampTime2 = 100,
    .direction = 0,
};
/*=============================================================================
 =======                              METHODS                           =======
 =============================================================================*/

/* -----------------------------------------------------
 * --               Public functions                  --
 * ----------------------------------------------------- */

/* -----------------------------------------------------
 * --               Private functions                  --
 * ----------------------------------------------------- */
