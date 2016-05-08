/*!
***     \file	  BLDC_I2C_Hdlr.c
***     \ingroup  BLDC_I2C_Hdlr
***     \author   Daniel
***     \date	  9/27/2015 10:37:02 PM
***     \brief    TODO
***
******************************************************************************/

/*=============================================================================
 =======                            INCLUDES                             =======
 =============================================================================*/
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "drivers/I2C/I2C_slave.h"
#include "BLDC/BLDC.h"
#include "ServoInput/ServoInput.h"
#include "MotorController.h"

/*=============================================================================
 =======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
 =============================================================================*/

/*=============================================================================
 =======                       CONSTANTS  &  TYPES                       =======
 =============================================================================*/

/*=============================================================================
 =======                VARIABLES & MESSAGES & RESSOURCEN                =======
 =============================================================================*/
uint16_t tempU16;
uint8_t tempU8;

/*=============================================================================
 =======                              METHODS                           =======
 =============================================================================*/

/* -----------------------------------------------------
 * --               Public functions                  --
 * ----------------------------------------------------- */
bool I2C_Cmd_Callback(uint8_t cmd, volatile void *param, uint8_t paramLen)
{
	bool result = false;
	volatile BLDC_Status_t *bldcStatus_p;
    
    bldcStatus_p = BLDC_GetStatus();
        
	switch (cmd)
	{
		case I2C_CMD_TO_FBL:
		/* FBL Byte setzen, Reset  */
		if (bldcStatus_p->curState == BLDC_STATE_STOP)
		{
        }            
		break;
		
		case I2C_CMD_ARM:
        MC_ArmI2C();
		break;
			
		case I2C_CMD_SAVE_CONFIG:
		if (bldcStatus_p->curState != BLDC_STATE_STOP)
		{
/*			bldc_WriteConfigData();*/
			result = true;
		}
		break;

		case I2C_CMD_SET_CONFIG:
		if (bldcStatus_p->curState == BLDC_STATE_STOP)
		{
			
		}
		break;

		case I2C_CMD_SET_THROTTLE:
        if (1 == paramLen)
        {
            MC_SetThrottleValue_I2C(((uint8_t*)param)[0]);            
        }
		break;

		case I2C_CMD_GET_THROTTLE:
		result = true;
        tempU8 = MC_GetThrottle();
        I2C_SetTransmitBuffer(sizeof(uint8_t), (void*)&tempU8);
		break;
				
		case I2C_CMD_GET_PPM:
		result = true;
        tempU16 = SVI_GetPulseDuration();
		I2C_SetTransmitBuffer(sizeof(uint16_t), (void*)&tempU16);
		break;
		
		case I2C_CMD_GET_STATUS:
		result = true;
		I2C_SetTransmitBuffer(sizeof(BLDC_Status_t), (void*)bldcStatus_p);
		break;
		
		case I2C_CMD_GET_CONFIG:
		if (bldcStatus_p->curState == BLDC_STATE_STOP)
		{
			I2C_SetTransmitBuffer(sizeof(BLDC_Config_t), (void*)BLDC_GetConfig());
            result = true;
		}
		break;
		
		default:
		break;
	}

	return result;
}

/* -----------------------------------------------------
 * --               Private functions                  --
 * ----------------------------------------------------- */

/* EOF */