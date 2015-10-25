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
uint16_t tempU16;
uint8_t tempU8;

/*=============================================================================
 =======                              METHODS                           =======
 =============================================================================*/

/* -----------------------------------------------------
 * --               Public functions                  --
 * ----------------------------------------------------- */
bool SPI_Cmd_Callback(uint8_t cmd, volatile void *param, uint8_t paramLen)
{
	bool result = false;
	BLDC_Status_t *bldcStatus_p;
    
    bldcStatus_p = BLDC_GetStatus();
        
	switch (cmd)
	{
		case SPI_CMD_RESET:
		/* Reset */
		if (bldcStatus_p->curState == BLDC_STATE_STOP)
		{
            do 
            {
                asm("NOP");
            } while (1);
        }        
		break;
		
		case SPI_CMD_TO_FBL:
		/* FBL Byte setzen, Reset  */
		if (bldcStatus_p->curState == BLDC_STATE_STOP)
		{
        }            
		break;
		
		case SPI_CMD_ARM:
        MC_ArmSPI();
		break;
			
		case SPI_CMD_SAVE_CONFIG:
		if (bldcStatus_p->curState != BLDC_STATE_STOP)
		{
			bldc_WriteConfigData();
			result = true;
		}
		break;

		case SPI_CMD_SET_CONFIG:
		if (bldcStatus_p->curState == BLDC_STATE_STOP)
		{
			
		}
		break;

		case SPI_CMD_SET_THROTTLE:
        if (1 == paramLen)
        {
            MC_SetThrottleValue_SPI(param[0]);            
        }
		break;

		case SPI_CMD_GET_THROTTLE:
		result = true;
        tempU8 = MC_GetThrottle();
        SPI_SetTransmitBuffer(sizeof(uint8_t), (void*)&tempU8);
		break;
				
		case SPI_CMD_GET_PPM:
		result = true;
        tempU16 = SVI_GetPulseDuration();
		SPI_SetTransmitBuffer(sizeof(uint16_t), (void*)&tempU16);
		break;
		
		case SPI_CMD_GET_STATUS:
		result = true;
		SPI_SetTransmitBuffer(sizeof(bldc_Status), (void*)bldcStatus_p);
		break;
		
		case SPI_CMD_GET_CONFIG:
		if (bldcStatus_p->curState == BLDC_STATE_STOP)
		{
			SPI_SetTransmitBuffer(sizeof(bldc_Config), (void*)BLDC_GetConfig());
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
