/*!
***     \file	  SPI_slave.c
***     \ingroup  SPI_slave
***     \author   Daniel
***     \date	  9/26/2015 6:50:50 PM
***     \brief    SPI slave Implementation
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
#include <util/crc16.h>
#include "SPI_slave.h"
/*=============================================================================
 =======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
 =============================================================================*/
#define SPI_RECV_BUFFER_LEN 10
/*=============================================================================
 =======                       CONSTANTS  &  TYPES                       =======
 =============================================================================*/

/*=============================================================================
 =======                VARIABLES & MESSAGES & RESSOURCEN                =======
 =============================================================================*/
static volatile bool spi_CmdActive;
static volatile uint8_t spi_RecvCmd;
static volatile uint8_t spi_RecvBufferPos;
static volatile uint8_t spi_Crc;
static volatile uint8_t spi_RecvBuffer[SPI_RECV_BUFFER_LEN];
static volatile uint8_t spi_SendBufferPos;
static volatile uint8_t spi_SendBufferLen;
static volatile uint8_t *spi_SendBuffer;

SPI_Cmd_Data_t spi_Config[SPI_NUM_CMDS];
/*=============================================================================
 =======                              METHODS                           =======
 =============================================================================*/
extern bool SPI_Cmd_Callback(uint8_t cmd, volatile void *param, uint8_t paramLen);
/* -----------------------------------------------------
 * --               Public functions                  --
 * ----------------------------------------------------- */
void SPI_SlaveInit(void)
{
	SPCR = _BV(SPIE)|_BV(SPE);
}

void SPI_SetTransmitBuffer(uint8_t bufLen, void *data)
{
	spi_SendBufferLen = bufLen;
	spi_SendBufferPos = 0;
	spi_SendBuffer = data;
}
/* -----------------------------------------------------
 * --               Private functions                  --
 * ----------------------------------------------------- */
uint8_t spi_GetCmdIndex(uint8_t cmd)
{
	uint8_t ctr = 0;
	while ((spi_Config[ctr].cmd != cmd) && (ctr < (SPI_NUM_CMDS-1)))
	{
		ctr++;
	}
	
	return ctr;
}

ISR(SPI_STC_vect, ISR_NOBLOCK)
{
	uint8_t cmdIndex = SPI_NUM_CMDS;

	if (false == spi_CmdActive)
	{
        spi_Crc = 0;
        
		spi_RecvCmd = SPDR;
		cmdIndex = spi_GetCmdIndex(spi_RecvCmd);
		if (cmdIndex < SPI_NUM_CMDS)
		{
			spi_CmdActive = true;
            spi_Crc = _crc8_ccitt_update(spi_Crc, spi_RecvCmd);
            
			if (spi_Config[cmdIndex].paramLen != 0)
			{
				spi_RecvBufferPos = 0;
			}
		}
	}
	else
	{
        if (cmdIndex < SPI_NUM_CMDS)
        {
		    if (spi_RecvBufferPos < spi_Config[cmdIndex].paramLen)
		    {
    		    spi_RecvBuffer[spi_RecvBufferPos] = SPDR;
    		
    		    if ((spi_RecvBufferPos == (spi_Config[cmdIndex].paramLen - 1)))
    		    {
        		    if (spi_Crc == spi_RecvBuffer[spi_RecvBufferPos])
        		    {
            		    spi_SendBufferPos = 0;
            		    spi_Crc = 0;
            		    spi_CmdActive = SPI_Cmd_Callback(spi_RecvCmd, spi_RecvBuffer, spi_Config[cmdIndex].paramLen - 1);
        		    }
    		    }
    		    else
    		    {
        		    spi_Crc = _crc8_ccitt_update(spi_Crc, spi_RecvBuffer[spi_RecvBufferPos]);
        		    spi_RecvBufferPos++;
    		    }
		    }
		    else
		    {
    		    if (spi_SendBufferPos < spi_SendBufferLen)
    		    {
        		    SPDR = spi_SendBuffer[spi_SendBufferPos];
        		    spi_Crc = _crc8_ccitt_update(spi_Crc, spi_SendBuffer[spi_SendBufferPos]);
        		    spi_SendBufferPos++;
    		    }
    		    else if (spi_SendBufferPos == spi_SendBufferLen)
    		    {
        		    SPDR = spi_Crc;
        		    spi_CmdActive = false;
        		    spi_SendBufferPos++;
    		    }
    		    else
    		    {
        		    SPDR = 0;
    		    }
		    }
        }            
	}
}
/* EOF */