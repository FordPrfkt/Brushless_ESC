/*!
***     \file	  BLDC_SPI_Hdlr.c
***     \ingroup  BLDC_SPI_Hdlr
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
#include "drivers/SPI/SPI_slave.h"
#include "BLDC.h"

/*=============================================================================
 =======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
 =============================================================================*/

/*=============================================================================
 =======                       CONSTANTS  &  TYPES                       =======
 =============================================================================*/

/*=============================================================================
 =======                VARIABLES & MESSAGES & RESSOURCEN                =======
 =============================================================================*/
extern BLDC_Config_t bldc_Config;
uint16_t bldc_RPMSetpopint;
/*=============================================================================
 =======                              METHODS                           =======
 =============================================================================*/
extern void bldc_WriteConfigData(void);
/* -----------------------------------------------------
 * --               Public functions                  --
 * ----------------------------------------------------- */
bool SPI_Cmd_Callback(uint8_t cmd, volatile void *param, uint8_t paramLen)
{
	bool result = false;
	
	switch (cmd)
	{
		case SPI_CMD_RESET:
		/* Reset */
		break;
		
		case SPI_CMD_TO_FBL:
		/* FBL Byte setzen, Reset  */
		break;
		
		case SPI_CMD_ARM:
		if (bldc_Status.curState == BLDC_STATE_STOP)
		{
			
		}
		break;
		
		case SPI_CMD_START:
		if (bldc_Status.curState == BLDC_STATE_STOP)
		{
			
		}
		break;
		
		case SPI_CMD_STOP:
		if (bldc_Status.curState != BLDC_STATE_STOP)
		{
			
		}
		break;
		
		case SPI_CMD_SAVE_CONFIG:
		if (bldc_Status.curState != BLDC_STATE_STOP)
		{
			bldc_WriteConfigData();
			result = true;
		}
		break;

		case SPI_CMD_SET_CONFIG:
		if (bldc_Status.curState == BLDC_STATE_STOP)
		{
			
		}
		break;
		
		case SPI_CMD_SET_SPEED:
		result = true;
		bldc_RPMSetpopint = *((uint16_t*)param);
		break;
		
		case SPI_CMD_GET_SETSPEED:
		result = true;
		SPI_SetTransmitBuffer(sizeof(bldc_RPMSetpopint), (void*)&bldc_RPMSetpopint);
		break;
		
		case SPI_CMD_GET_PPM:
		result = true;
		SPI_SetTransmitBuffer(sizeof(bldc_PWMValue), (void*)&bldc_PWMValue);
		break;
		
		case SPI_CMD_GET_STATUS:
		result = true;
		SPI_SetTransmitBuffer(sizeof(bldc_Status), (void*)&bldc_Status);
		break;
		
		case SPI_CMD_GET_CONFIG:
		if (bldc_Status.curState == BLDC_STATE_STOP)
		{
			SPI_SetTransmitBuffer(sizeof(bldc_Config), (void*)&bldc_Config);	
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
