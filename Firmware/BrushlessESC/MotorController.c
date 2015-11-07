/*!
***     \file	  MotorController.c
***     \ingroup  MotorController
***     \author   Daniel
***     \date	  10/18/2015 12:51:06 AM
***     \brief    TODO
***
******************************************************************************/

/*=============================================================================
=======                            INCLUDES                             =======
=============================================================================*/
#include <stdint.h>
#include <stdbool.h>
#include <avr/eeprom.h>
#include "ServoInput/ServoInput.h"
#include "config/MotorController_config.h"
#include "BLDC/BLDC.h"
#include "LED/LED.h"
#include "MotorController.h"
/*=============================================================================
=======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
=============================================================================*/
#define MC_THROTTLE_CAL_DURATION ((MC_MIN_PULSE_DURATION + MC_MAX_PULSE_DURATION) / 2)
#define  MC_CLEAR_TEMP() (temp1 = temp2 = temp3 = 0)

/*=============================================================================
=======                       CONSTANTS  &  TYPES                       =======
=============================================================================*/

/*=============================================================================
=======                VARIABLES & MESSAGES & RESSOURCEN                =======
=============================================================================*/
static enum {MC_PPM_INPUT, MC_SPI_INPUT} mc_Input;
static MC_State_t mc_State;
static bool noRunYet;
static uint16_t temp1, temp2, temp3;
static uint16_t lastValidPulseDuration;
static uint8_t mc_ThrottleVal;
static uint8_t mc_ThrottleTimeoutCtr;
static uint8_t mc_pwmStep;

/* EEPROM Daten */
static MC_Config_t mc_ConfigData;
static BLDC_Config_t mc_bldcConfigData;
/* END EEPROM Daten */
/*=============================================================================
=======                              METHODS                           =======
=============================================================================*/
uint8_t mc_GetThrottleInputPPM(uint16_t pulseDuration);
MC_State_t mc_DoDisarmedCheck(uint16_t pulseDuration, uint8_t timeInterval);
MC_State_t mc_DoCalibrateMax(uint16_t pulseDuration, uint8_t timeInterval);
MC_State_t mc_DoCalibrateMin(uint16_t pulseDuration, uint8_t timeInterval);
void mc_PlaySound(void);
void mc_SetError(uint8_t errorID, bool continueOperation);

/* -----------------------------------------------------
* --               Public functions                  --
* ----------------------------------------------------- */
void MC_Init(void)
{
    noRunYet = true;
    mc_Input = MC_PPM_INPUT;
    mc_State = MC_STATE_STARTUP;
    lastValidPulseDuration = 0;
    mc_ThrottleVal = 0;
    mc_ThrottleTimeoutCtr = 0;
    mc_pwmStep = 0;
    MC_CLEAR_TEMP();
    
    /* Resetgrund lesen und ggf. speichern */
    if ((MCUSR & WDRF) == WDRF)
    {
        /* Watchdog Reset */
        mc_SetError(MC_ERROR_WDG_RESET, true);
        MCUSR |= WDRF;
    }
        
    if ((MCUSR & WDRF) == BORF)
    {
        /* Brownout Reset */
        mc_SetError(MC_ERROR_BROWNOUT_RESET, true);
        MCUSR |= BORF;
    }
    
  	eeprom_read_block(&mc_ConfigData, &MC_ConfigDataEE, sizeof(MC_Config_t));
    eeprom_read_block(&mc_bldcConfigData, &MC_bldcConfigDataEE, sizeof(BLDC_Config_t));

    mc_pwmStep = (mc_ConfigData.throttleFullDuration * 10) / MC_PWM_STEPS;
    
    BLDC_Init(&mc_bldcConfigData);
    SVI_Start();
}

void MC_SetThrottleValue_SPI(uint8_t throttleValue)
{
    if (MC_SPI_INPUT == mc_Input)
    {
        mc_ThrottleVal = throttleValue;
        mc_ThrottleTimeoutCtr = 0;
    }
}

void MC_ArmSPI(void)
{
    if ((MC_PPM_INPUT == mc_Input) && ((MC_STATE_DISARMED == mc_State)||(MC_STATE_ARMED == mc_State)))
    {
        mc_Input = MC_SPI_INPUT;
        mc_State = MC_STATE_ARMED;
    }
}

void MC_GetErrorMemory(uint8_t errorMem[], uint8_t *lastError)
{
    *lastError = eeprom_read_byte(&MC_LastErrorEE);
    eeprom_read_block(errorMem, &MC_ErrorMemoryEE, 10);
}

uint8_t MC_GetThrottle(void)
{
    return mc_ThrottleVal;
}

void MC_Cyclic_1ms(void)
{
    uint16_t ppmInputValue = SV_NO_PULSE;
    uint16_t armingTimeout = 0;
    
    switch (mc_Input)
    {
        case MC_SPI_INPUT:        
        if (mc_ConfigData.throttleTimeout <= mc_ThrottleTimeoutCtr)
        {
            mc_ThrottleVal = UINT8_MAX;
        }
        else
        {
            mc_ThrottleTimeoutCtr += MC_LOOP_INTERVAL;            
        }
        break;
        
        case MC_PPM_INPUT:
        ppmInputValue = SVI_GetPulseDuration();

        if (mc_ConfigData.throttleTimeout > mc_ThrottleTimeoutCtr)
        {
            if ((MC_MIN_PULSE_DURATION > ppmInputValue) || (MC_MAX_PULSE_DURATION < ppmInputValue))
            {
                ppmInputValue = lastValidPulseDuration;
                mc_ThrottleTimeoutCtr += MC_LOOP_INTERVAL;
            }
            else
            {
                if (mc_ConfigData.throttleFullDuration < ppmInputValue)
                {
                    ppmInputValue = mc_ConfigData.throttleFullDuration;
                }
                else if (mc_ConfigData.throttleOffDuration > ppmInputValue)
                {
                    ppmInputValue = mc_ConfigData.throttleOffDuration;
                }
                else
                {
                    /*  */
                }

                lastValidPulseDuration = ppmInputValue;

                if (0 < mc_ThrottleTimeoutCtr)
                {
                    mc_ThrottleTimeoutCtr -= MC_LOOP_INTERVAL;
                }
            }

            mc_ThrottleVal = mc_GetThrottleInputPPM(ppmInputValue);
        }
        else
        {
            mc_ThrottleVal = UINT8_MAX;
        }
        break;
        
        default:
        mc_ThrottleVal = UINT8_MAX;
        break;
    }
    
    switch(mc_State)
    {
        case MC_STATE_STARTUP:
        /* Startmelodie */
        mc_State = MC_STATE_DISARMED;
        armingTimeout = 0;
        MC_CLEAR_TEMP();
        break;
        
        case MC_STATE_DISARMED:        
        armingTimeout += MC_LOOP_INTERVAL;
        if (MC_ARMING_TIMEOUT > armingTimeout)
        {
            if (MC_PPM_INPUT == mc_Input)
            {
                mc_State = mc_DoDisarmedCheck(ppmInputValue, MC_LOOP_INTERVAL);
            }
            else
            {
                mc_State = MC_STATE_ARMED;
            }            
        }
        else
        {
            MC_CLEAR_TEMP();
            mc_SetError(MC_ERROR_ARMING_TIMEOUT, false);
        }
        break;
        
        case MC_STATE_CALIBRATE_MAX:
        if (MC_PPM_INPUT == mc_Input)
        {
            mc_State = mc_DoCalibrateMax(ppmInputValue, MC_LOOP_INTERVAL);            
        }
        else
        {
            mc_SetError(MC_ERROR_INTERNAL, false);
        }
        break;
        
        case MC_STATE_CALIBRATE_MIN:
        if (MC_PPM_INPUT == mc_Input)
        {
            mc_State = mc_DoCalibrateMin(ppmInputValue, MC_LOOP_INTERVAL);
        }        
        else
        {
            mc_SetError(MC_ERROR_INTERNAL, false);
        }
        break;

        case MC_STATE_ARMED:
        LED_On();
        if (UINT8_MAX == mc_ThrottleVal)
        {
            mc_SetError(MC_ERROR_NO_SIGNAL, false);
        }
        else
        {
            if (0 < mc_ThrottleVal)
            {
                temp1++;
            }
            else
            {
                temp1 = 0;
            }

            /* Sobald Gas > 0 für 50ms, Motor anwerfen, dann weiter zu running */
            if (MC_START_TIMEOUT < temp1)
            {
                MC_CLEAR_TEMP();
                mc_State = MC_STATE_RUNNING;
                LED_Off();
                BLDC_StartMotor();
                BLDC_SetPower(mc_ThrottleVal);
            }
        }
        break;
        
        case MC_STATE_RUNNING:

        if (UINT8_MAX != mc_ThrottleVal)
        {
            /* Wenn Gas = 0, Motor stoppen */
            if (0 == mc_ThrottleVal)
            {
                BLDC_StopMotor(false);
                mc_State = MC_STATE_ARMED;
            }
            else
            {
                /* Sonst: Motorleistung setzen */
                BLDC_SetPower(mc_ThrottleVal);
            }
        }
        else
        {
            /* Throttle timeout */
            mc_SetError(MC_ERROR_NO_SIGNAL, false);
        }
        
        /* Motorfehler ueberwachen */
        if (BLDC_GetStatus()->error != BLDC_NO_ERROR)
        {
            mc_SetError((uint8_t)BLDC_GetStatus()->error, false);
        }
        
        /* Wenn Gas auf 0 geht und dann wieder hoch,
        * prüfen ob der Motor stillsteht oder direkt weiter kommutiert werden kann.
        * Wenn Motor länger Stillsteht, wieder zu Disarmed */
        break;
        
        case MC_STATE_ERROR:
        /* Nicht behebbarer Motorfehler. Power Off/On nötig. */
        break;
        
        default:
        break;
    }
}
/* -----------------------------------------------------
* --               Private functions                  --
* ----------------------------------------------------- */
uint8_t mc_GetThrottleInputPPM(uint16_t pulseDuration)
{
    uint8_t throttleVal = 0;
    
    if (UINT16_MAX > pulseDuration)
    {
        if (mc_ConfigData.throttleOffDuration == pulseDuration)
        {
            throttleVal = 0;
        }
        else if (mc_ConfigData.throttleFullDuration == pulseDuration)
        {
            throttleVal = MC_PWM_STEPS - 1;
        }
        else
        {
            pulseDuration = (pulseDuration * 10) / mc_pwmStep;
            if ((MC_PWM_STEPS - 1) < pulseDuration)
            {
                throttleVal = MC_PWM_STEPS - 1;
            }
            else
            {
                throttleVal = (uint8_t)pulseDuration;
            }
        }
    }
    else
    {
        throttleVal = UINT8_MAX;
    }
    
    return throttleVal;
}

MC_State_t mc_DoDisarmedCheck(uint16_t pulseDuration, uint8_t timeInterval)
{
    #define armingTimeout (temp1)
    #define throttleLowTimeout (temp2)
    #define throttleCalTimeout (temp3)
        
    /* Wenn Gas = 0 für 1s, weiter zu armed, sonst weiter zu calibrate */
    if (mc_ConfigData.throttleOffDuration >= pulseDuration)
    {
        throttleCalTimeout = 0;
        throttleLowTimeout += timeInterval;
        if (throttleLowTimeout >= mc_ConfigData.checkThrottleTime)
        {
            MC_CLEAR_TEMP();
            return MC_STATE_ARMED;
        }
    }
    else if ((MC_THROTTLE_CAL_DURATION >= pulseDuration) && (true == noRunYet))
    {
        throttleLowTimeout = 0;
        throttleCalTimeout += timeInterval;
        if (throttleCalTimeout >= MC_CHECK_CAL_TIME)
        {
            MC_CLEAR_TEMP();
            LED_Blink(500);
            return MC_STATE_CALIBRATE_MAX;
        }
    }
    else
    {
        /* */
    }
        
    return MC_STATE_DISARMED;

    #undef armingTimeout
    #undef throttleLowTimeout
    #undef throttleCalTimeout
}

MC_State_t mc_DoCalibrateMax(uint16_t pulseDuration, uint8_t timeInterval)
{
    #define calTimeout (temp1)
    #define lastPulseDuration (temp2)
    #define calTimer (temp3)

    calTimeout+=timeInterval;

    /* Wenn Gas > 0 und für 2s konstant, als max. Wert merken.
    * Wenn Gas anschliessend < max. Wert und für 2s konstant, als min Wert merken.
    * Dann weiter zu armed. */
    
    if (MC_THROTTLE_CAL_DURATION <= pulseDuration)
    {
        if (pulseDuration == lastPulseDuration)
        {
            calTimer++;
        }
        else
        {
            calTimer = 0;
        }
        lastPulseDuration = pulseDuration;
    }

    if (MC_CALIBRATE_TIME < calTimer)
    {
        mc_ConfigData.throttleFullDuration = pulseDuration;
        
        MC_CLEAR_TEMP();
        LED_Blink(300);
        return MC_STATE_CALIBRATE_MIN;
    }
    
    if (MC_CALIBRATION_TIMEOUT <= calTimeout)
    {
        MC_CLEAR_TEMP();
        return MC_STATE_ERROR;
    }

    return MC_STATE_CALIBRATE_MAX;

    #undef calTimeout
    #undef lastPulseDuration
    #undef calTimer
}

MC_State_t mc_DoCalibrateMin(uint16_t pulseDuration, uint8_t timeInterval)
{
    #define calTimeout (temp1)
    #define lastPulseDuration (temp2)
    #define calTimer (temp3)

    calTimeout+=timeInterval;

    /* Wenn Gas > 0 und für 2s konstant, als max. Wert merken.
    * Wenn Gas anschliessend < max. Wert und für 2s konstant, als min Wert merken.
    * Dann weiter zu armed. */
    
    if (MC_THROTTLE_CAL_DURATION > pulseDuration)
    {
        if (pulseDuration == lastPulseDuration)
        {
            calTimer++;
        }
        else
        {
            calTimer = 0;
        }
        lastPulseDuration = pulseDuration;
    }

    if (MC_CALIBRATE_TIME < calTimer)
    {
        mc_ConfigData.throttleOffDuration = pulseDuration;
        eeprom_write_block(&mc_ConfigData, &MC_ConfigDataEE, sizeof(MC_Config_t));    
        
        MC_CLEAR_TEMP();
        return MC_STATE_ARMED;
    }
    
    if (MC_CALIBRATION_TIMEOUT <= calTimeout)
    {
        MC_CLEAR_TEMP();
        mc_SetError(MC_ERROR_CAL_TIMEOUT, false);
        return MC_STATE_ERROR;
    }

    return MC_STATE_CALIBRATE_MIN;

    #undef calTimeout
    #undef lastPulseDuration
    #undef calTimer
}

void mc_PlaySound(void)
{
    
}

void mc_SetError(uint8_t errorID, bool continueOperation)
{
    uint8_t lastError;
    uint8_t curError;

    if (false == continueOperation)
    {
        mc_State = MC_STATE_ERROR;
        LED_Blink(100);
        BLDC_StopMotor(true);        
    }

    lastError = eeprom_read_byte(&MC_LastErrorEE);
    curError = eeprom_read_byte(&MC_ErrorMemoryEE[lastError]);
    
    if (curError != errorID)
    {
        lastError++;
        lastError%=10;
        eeprom_write_byte(&MC_ErrorMemoryEE[lastError], errorID);
        eeprom_write_byte(&MC_LastErrorEE, lastError);
    }
}

/* TODO: Beim anfahren prüfen ob der Motor schon dreht */
/* TODO: Soundausgabe */
/* TODO: Selbsttest */
/* TODO: Anfahrrampe berechnen */

/* EOF */