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
#include <string.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <util/crc16.h>
#include "drivers/TWI/TWI_slave.h"
#include "BLDC/BLDC.h"
#include "ServoInput/ServoInput.h"
#include "MotorController.h"
#include "TWI_Handler.h"

/*=============================================================================
 =======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
 =============================================================================*/
#define TWI_SLAVE_ADDRESS (0x42)

/*=============================================================================
 =======                       CONSTANTS  &  TYPES                       =======
 =============================================================================*/
const TWI_Reg_Data_t twi_RegisterConfig[TWI_NUM_REGISTERS] = 
{
  {TWI_CMD_TO_FBL, 1},
  {TWI_CMD_CONFIG, 1},
  {TWI_CMD_SAVE_CONFIG, 1},
  {TWI_CMD_ARM, 1},
  {TWI_CMD_THROTTLE, 1},
  {TWI_CMD_PPM, 1},
  {TWI_CMD_STATUS, 1},
  {TWI_CMD_ERRORS, 1}
};
/*=============================================================================
 =======                VARIABLES & MESSAGES & RESSOURCEN                =======
 =============================================================================*/
uint16_t tempU16;
uint8_t rxBuf[TWI_BUFFER_SIZE];
uint8_t txBuf[TWI_BUFFER_SIZE];

/*=============================================================================
 =======                              METHODS                           =======
 =============================================================================*/
uint8_t twi_GetCmdIndex(uint8_t cmd);
uint8_t twi_GetCRC(uint8_t *data, uint8_t dataLen);

/* -----------------------------------------------------
 * --               Public functions                  --
 * ----------------------------------------------------- */
void TWI_Init(void)
{
    memset(rxBuf, 0, TWI_BUFFER_SIZE);
    TWI_Slave_Initialise(TWI_SLAVE_ADDRESS<<TWI_ADR_BITS);
    TWI_Start_Transceiver();
}

void TWI_MainLoop(void)
{
    volatile BLDC_Status_t *bldcStatus_p;
    uint8_t cmdIdx = TWI_NUM_REGISTERS;
    uint8_t crc;
    bool read;
    
    if (1 == TWI_statusReg.RxDataInBuf)
    {
        TWI_Get_Data_From_Transceiver(rxBuf, TWI_BUFFER_SIZE);
        
        read = ((rxBuf[0] & (1 << TWI_READ_BIT)) == (1 << TWI_READ_BIT)) ? true:false;
        cmdIdx = twi_GetCmdIndex(rxBuf[1]);
        crc = twi_GetCRC(&rxBuf[1], twi_RegisterConfig[cmdIdx].dataLen + 1);
        
        if ((cmdIdx < TWI_NUM_REGISTERS) && (crc == rxBuf[twi_RegisterConfig[cmdIdx].dataLen - 1]))
        {
            bldcStatus_p = BLDC_GetStatus();

            switch (rxBuf[1])
            {
                case TWI_CMD_TO_FBL:
                /* FBL Byte setzen, Reset  */
                if ((bldcStatus_p->curState == BLDC_STATE_STOP) && (false == read))
                {
                }
                break;
                	
                case TWI_CMD_ARM:
                if (true == read)
                {
                    
                }
                else
                {
                    MC_ArmTWI();                    
                }
                break;
                	
                case TWI_CMD_SAVE_CONFIG:
                if ((bldcStatus_p->curState != BLDC_STATE_STOP) && (false == read))
                {
                    /*			bldc_WriteConfigData();*/
                }
                break;

                case TWI_CMD_CONFIG:
                if (bldcStatus_p->curState == BLDC_STATE_STOP)
                {
                    if (true == read)
                    {
                        memcpy(txBuf, (void*)BLDC_GetConfig(), sizeof(BLDC_Config_t));
                        TWI_Start_Transceiver_With_Data(txBuf, sizeof(BLDC_Config_t));
                    }
                    else
                    {
                        
                    }
                }
                break;

                case TWI_CMD_THROTTLE:
                if (true == read)
                {
                    txBuf[0] = MC_GetThrottle();
                    TWI_Start_Transceiver_With_Data(txBuf, sizeof(uint8_t));
                }
                else
                {
                    MC_SetThrottleValue_TWI(((uint8_t*)rxBuf)[2]);
                }                                        
                break;
               	
                case TWI_CMD_PPM:
                if (true == read)
                {
                tempU16 = SVI_GetPulseDuration();
                memcpy(txBuf, &tempU16, sizeof(uint16_t));
                TWI_Start_Transceiver_With_Data(txBuf, sizeof(uint16_t));
                }
                break;
                	
                case TWI_CMD_STATUS:
                if (true == read)
                {
                memcpy(txBuf, (volatile const void*)bldcStatus_p, sizeof(BLDC_Status_t));
                TWI_Start_Transceiver_With_Data(txBuf, sizeof(BLDC_Status_t));
                }
                break;
                	                	
                default:
                break;
            }
        }
        
        memset(rxBuf, 0, TWI_BUFFER_SIZE);
    }
}

/* -----------------------------------------------------
 * --               Private functions                  --
 * ----------------------------------------------------- */
uint8_t twi_GetCmdIndex(uint8_t cmd)
{
    uint8_t ctr = 0;
    while ((twi_RegisterConfig[ctr].reg != cmd) && (ctr < (TWI_NUM_REGISTERS-1)))
    {
        ctr++;
    }
    
    return ctr;
}

uint8_t twi_GetCRC(uint8_t *data, uint8_t dataLen)
{
    uint8_t ctr;
    uint8_t crc = 0;
    
    for (ctr = 0; ctr < dataLen; ctr++)
    {
        crc = _crc8_ccitt_update(crc, data[ctr]);    
    }
    
    return crc;
}

/* EOF */