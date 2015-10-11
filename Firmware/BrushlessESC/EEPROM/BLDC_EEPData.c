/*
 * BLDC_EEPData.c
 *
 * Created: 03.10.2015 15:24:43
 *  Author: Daniel
 */ 
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/eeprom.h>
#include "../BLDC.h"

static BLDC_Config_t bldc_ConfigDefault EEMEM = 
{
	.escID = UINT16_MAX,
    .maxCurrent = 1,
	.minVoltage = 1,
	.maxVoltage = 1,
	.motorConstant = 950,
	.alignTime = 1000,
	.rampPwm1 = 10,
	.rampPwm2 = 60,
	.rampTime1 = 10,
	.rampTime2 = 100,
	.pwmMin = 10,
	.pwmMax = 10,
	.direction = 0,
	.autoArm = 0,
	.beepOnStart = 1,
	.beepOnError = 1,
	.autoCurrentLimit = 1
};

static BLDC_ServoCalData_t BLDC_ServoCalDataDefault EEMEM = 
{
    .minGas = UINT16_MAX,
    .maxGas = UINT16_MAX,
    .idleGas = UINT16_MAX    
};

static BLDC_Error_t bldc_ErrorMemory[10] EEMEM = 
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

static uint8_t bldc_LastError EEMEM = 0;

BLDC_Config_t bldc_Config;
BLDC_ServoCalData_t BLDC_ServoCalData;

void bldc_ReadConfigData(void)
{
	eeprom_read_block(&bldc_Config, &bldc_ConfigDefault, sizeof(BLDC_Config_t));
}

void bldc_WriteConfigData(void)
{
	eeprom_write_block(&bldc_Config, &bldc_ConfigDefault, sizeof(BLDC_Config_t));
}

void bldc_ReadServoCalData(void)
{
    eeprom_read_block(&BLDC_ServoCalData, &BLDC_ServoCalDataDefault, sizeof(BLDC_ServoCalData_t));
}

void bldc_WriteServoCalData(void)
{
    eeprom_write_block(&BLDC_ServoCalData, &BLDC_ServoCalDataDefault, sizeof(BLDC_ServoCalData_t));
}

void bldc_StoreError(BLDC_Error_t error)
{
    uint8_t lastError;
    BLDC_Error_t curError;
    
    lastError = eeprom_read_byte(&bldc_LastError);
    eeprom_read_block(&curError, &bldc_ErrorMemory[lastError], sizeof(BLDC_Error_t));
    
    if (curError != error)
    {
        lastError++;
        lastError%=10;
        eeprom_write_block(&error, &bldc_ErrorMemory[lastError], sizeof(BLDC_Error_t));
        eeprom_write_byte(&bldc_LastError, lastError);        
    }
}

void bldc_GetErrorMemory(BLDC_Error_t errorMem[], uint8_t *lastError)
{
    *lastError = eeprom_read_byte(&bldc_LastError);
    eeprom_read_block(errorMem, &bldc_ErrorMemory, sizeof(bldc_ErrorMemory));
}