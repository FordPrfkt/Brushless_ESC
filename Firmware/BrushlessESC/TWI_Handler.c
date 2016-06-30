/*!
***     \file	  BLDC_TWI_Hdlr.c
***     \ingroup  BLDC_TWI_Hdlr
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
#include "drivers/TWI/TWI_slave.h"
#include "BLDC/BLDC.h"
#include "ServoInput/ServoInput.h"
#include "MotorController.h"

/*=============================================================================
 =======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
 =============================================================================*/
#define TWI_SLAVE_ADDRESS (0x42)

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
void TWI_Init(void)
{
    TWI_Slave_Initialise(TWI_SLAVE_ADDRESS<<TWI_ADR_BITS);
    TWI_Start_Transceiver();
}

void TWI_MainLoop(void)
{
    uint8_t rxBuf[TWI_BUFFER_SIZE];
    uint8_t cmdIdx = TWI_NUM_CMDS;
    bool read;
    
    if (1 == TWI_statusReg.RxDataInBuf)
    {
        TWI_Get_Data_From_Transceiver(rxBuf, TWI_BUFFER_SIZE);
        
        read = ((rxBuf[0] & (1 << TWI_READ_BIT)) == (1 << TWI_READ_BIT)) ? true:false;
        cmdIdx = twi_GetCmdIndex(rxBuf[1]);
       
        if (cmdIdx < TWI_NUM_CMDS)
        {
            TWI_Cmd_Callback(rxBuf[1], &rxBuf[2], twi_Config[cmdIdx].paramLen);
        }
    }
}

bool TWI_Cmd_Callback(uint8_t cmd, volatile void *param, uint8_t paramLen)
{
	bool result = false;
	volatile BLDC_Status_t *bldcStatus_p;
    
    bldcStatus_p = BLDC_GetStatus();
        
	switch (cmd)
	{
		case TWI_CMD_TO_FBL:
		/* FBL Byte setzen, Reset  */
		if (bldcStatus_p->curState == BLDC_STATE_STOP)
		{
        }            
		break;
		
		case TWI_CMD_ARM:
        MC_ArmTWI();
		break;
			
		case TWI_CMD_SAVE_CONFIG:
		if (bldcStatus_p->curState != BLDC_STATE_STOP)
		{
/*			bldc_WriteConfigData();*/
			result = true;
		}
		break;

		case TWI_CMD_CONFIG:
		if (bldcStatus_p->curState == BLDC_STATE_STOP)
		{
			
		}
		break;

		case TWI_CMD_THROTTLE:
        if (1 == paramLen)
        {
            MC_SetThrottleValue_TWI(((uint8_t*)param)[0]);            
        }
		break;

		case TWI_CMD_THROTTLE:
		result = true;
        tempU8 = MC_GetThrottle();
        TWI_SetTransmitBuffer(sizeof(uint8_t), (void*)&tempU8);
		break;
				
		case TWI_CMD_PPM:
		result = true;
        tempU16 = SVI_GetPulseDuration();
		TWI_SetTransmitBuffer(sizeof(uint16_t), (void*)&tempU16);
		break;
		
		case TWI_CMD_STATUS:
		result = true;
		TWI_SetTransmitBuffer(sizeof(BLDC_Status_t), (void*)bldcStatus_p);
		break;
		
		case TWI_CMD_CONFIG:
		if (bldcStatus_p->curState == BLDC_STATE_STOP)
		{
			TWI_SetTransmitBuffer(sizeof(BLDC_Config_t), (void*)BLDC_GetConfig());
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
uint8_t twi_GetCmdIndex(uint8_t cmd)
{
    uint8_t ctr = 0;
    while ((twi_Config[ctr].cmd != cmd) && (ctr < (TWI_NUM_CMDS-1)))
    {
        ctr++;
    }
    
    return ctr;
}

/* EOF */