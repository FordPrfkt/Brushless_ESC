/*!
***     \file	  I2C.c
***     \ingroup  I2C
***     \author   Daniel
***     \date	  07.11.2015 16:44:34
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
#include <util/crc16.h>
#include <util/twi.h>
#include "I2C.h"
/*=============================================================================
 =======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
 =============================================================================*/
#define I2C_RECV_BUFFER_LEN 10
#define I2C_SLAVE_ADDRESS (0x42)

/*=============================================================================
 =======                       CONSTANTS  &  TYPES                       =======
 =============================================================================*/

/*=============================================================================
 =======                VARIABLES & MESSAGES & RESSOURCEN                =======
 =============================================================================*/
static volatile bool i2c_CmdActive;
static volatile uint8_t i2c_RecvCmd;
static volatile uint8_t i2c_RecvBufferPos;
static volatile uint8_t i2c_Crc;
static volatile uint8_t i2c_RecvBuffer[I2C_RECV_BUFFER_LEN];
static volatile uint8_t i2c_SendBufferPos;
static volatile uint8_t i2c_SendBufferLen;
static volatile uint8_t *i2c_SendBuffer;

I2C_Cmd_Data_t i2c_Config[I2C_NUM_CMDS];

/*=============================================================================
 =======                              METHODS                           =======
 =============================================================================*/
extern bool I2C_Cmd_Callback(uint8_t cmd, volatile void *param, uint8_t paramLen);

/* -----------------------------------------------------
 * --               Public functions                  --
 * ----------------------------------------------------- */
void I2C_SlaveInit(void)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        TWAR = I2C_SLAVE_ADDRESS;
        TWCR &= ~(_BV(TWSTA)|_BV(TWSTO));
        TWCR = _BV(TWEN)|_BV(TWEA)|_BV(TWIE)|_BV(TWINT);
    }
}

void I2C_SetTransmitBuffer(uint8_t bufLen, void *data)
{
    i2c_SendBufferLen = bufLen;
    i2c_SendBufferPos = 0;
    i2c_SendBuffer = data;
}

/* -----------------------------------------------------
 * --               Private functions                  --
 * ----------------------------------------------------- */
uint8_t i2c_GetCmdIndex(uint8_t cmd)
{
    uint8_t ctr = 0;
    while ((i2c_Config[ctr].cmd != cmd) && (ctr < (I2C_NUM_CMDS-1)))
    {
        ctr++;
    }
    
    return ctr;
}

ISR(TWI_vect, ISR_NOBLOCK)
{
    switch (TW_STATUS)
    {
        case TW_SR_SLA_ACK:
        break;
        
        case TW_SR_DATA_ACK:
        break;
        
        case TW_ST_SLA_ACK:
        case TW_ST_DATA_ACK:
        break;    
    }
    
    uint8_t cmdIndex = I2C_NUM_CMDS;

    if (false == i2c_CmdActive)
    {
        i2c_Crc = 0;
        
        i2c_RecvCmd = SPDR;
        cmdIndex = i2c_GetCmdIndex(i2c_RecvCmd);
        if (cmdIndex < I2C_NUM_CMDS)
        {
            i2c_CmdActive = true;
            i2c_Crc = _crc8_ccitt_update(i2c_Crc, i2c_RecvCmd);
            
            if (i2c_Config[cmdIndex].paramLen != 0)
            {
                i2c_RecvBufferPos = 0;
            }
        }
    }
    else
    {
        if (cmdIndex < I2C_NUM_CMDS)
        {
            if (i2c_RecvBufferPos < i2c_Config[cmdIndex].paramLen)
            {
                i2c_RecvBuffer[i2c_RecvBufferPos] = SPDR;
                
                if ((i2c_RecvBufferPos == (i2c_Config[cmdIndex].paramLen - 1)))
                {
                    if (i2c_Crc == i2c_RecvBuffer[i2c_RecvBufferPos])
                    {
                        i2c_SendBufferPos = 0;
                        i2c_Crc = 0;
                        i2c_CmdActive = I2C_Cmd_Callback(i2c_RecvCmd, i2c_RecvBuffer, i2c_Config[cmdIndex].paramLen - 1);
                    }
                }
                else
                {
                    i2c_Crc = _crc8_ccitt_update(i2c_Crc, i2c_RecvBuffer[i2c_RecvBufferPos]);
                    i2c_RecvBufferPos++;
                }
            }
            else
            {
                if (i2c_SendBufferPos < i2c_SendBufferLen)
                {
                    SPDR = i2c_SendBuffer[i2c_SendBufferPos];
                    i2c_Crc = _crc8_ccitt_update(i2c_Crc, i2c_SendBuffer[i2c_SendBufferPos]);
                    i2c_SendBufferPos++;
                }
                else if (i2c_SendBufferPos == i2c_SendBufferLen)
                {
                    SPDR = i2c_Crc;
                    i2c_CmdActive = false;
                    i2c_SendBufferPos++;
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