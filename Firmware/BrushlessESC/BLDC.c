/*!
***     \file	  BLDC.c
***     \ingroup  BLDC
***     \author   Daniel
***     \date	  9/19/2015 12:40:04 PM
***     \brief    TODO
***
******************************************************************************/

/*=============================================================================
=======                            INCLUDES                             =======
=============================================================================*/
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>
#include "Drivers/ACP/ACP.h"
#include "Drivers/ADC/ADC.h"
#include "Drivers/Timer/Timer1.h"
#include "Drivers/PWM/PWM.h"
#include "Drivers/SPI/SPI_slave.h"
#include "Filter/MovingAvgFilter.h"
#include "ServoInput/ServoInput.h"
#include "PID/PID_Controller.h"
#include "LED/LED.h"
#include "BLDC_config.h"
#include "BLDC.h"

/*=============================================================================
=======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
=============================================================================*/
/* Kommutierungsparameter */
#define IN_PIN_PWM_MODE 0
#define IN_PIN_CONSTANT_MODE 1
#define PHASE_LOW_SIDE 0
#define PHASE_HIGH_SIDE 1
#define PHASE_DISABLED 1
#define PHASE_ACTIVE 0
#define PHASE_A 0
#define PHASE_B 1
#define PHASE_C 2

/* Besondere Kommutierungseinstellungen */
#define BLDC_COMMUTATION_OFF 6
#define BLDC_COMMUTATION_QUICKSTOP 7

/*=============================================================================
=======                       CONSTANTS  &  TYPES                       =======
=============================================================================*/
typedef struct BLDC_CommutationState_s
{
    uint16_t phaseA_IN_DDR:1;
    uint16_t phaseA_IN:1;
    uint16_t phaseA_SD:1;
    uint16_t phaseB_IN_DDR:1;
    uint16_t phaseB_IN:1;
    uint16_t phaseB_SD:1;
    uint16_t phaseC_IN_DDR:1;
    uint16_t phaseC_IN:1;
    uint16_t phaseC_SD:1;
    uint16_t ComparatorInput:4;
    uint16_t BEMFPhase:2;
    uint16_t unused:1;
}BLDC_CommutationState_t;

typedef struct BLDC_Rampup_Table_s
{
    uint8_t pwmDuty;
    uint8_t commutationTime;
}BLDC_Rampup_Table_t;

/*
Zustand 	Phase A 	Phase B 	Phase C 	Stromfluss 	Komparator-Eingänge
1 			PWM 		Floating 	GND 		A --> C 	MITTEL <--> NULL_B
2 			Floating 	PWM 		GND 		B --> C 	MITTEL <--> NULL_A
3 			GND 		PWM 		Floating 	B --> A 	MITTEL <--> NULL_C
4 			GND 		Floating 	PWM 		C --> A 	MITTEL <--> NULL_B
5 			Floating 	GND 		PWM 		C --> B 	MITTEL <--> NULL_A
6 			PWM 		GND 		Floating 	A --> B 	MITTEL <--> NULL_C
Off			Floating	Floating	Floating
Quickstop	GND 		GND 		GND
*/
static const BLDC_CommutationState_t BLDC_CommutationStates[8] =
{
    /* PhaseA_IN_DDR		phaseA_IN		phaseA_SD		PhaseB_IN_DDR			phaseB_IN		phaseB_SD		PhaseC_IN_DDR			phaseC_IN		phaseC_SD		Comparator		BEMF Phase */
    {IN_PIN_PWM_MODE,		PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_DISABLED, IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_ACTIVE,	ACP_INPUT_ADC3,	PHASE_B, 0},
    {IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_DISABLED,	IN_PIN_PWM_MODE,		PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_ACTIVE,	ACP_INPUT_ADC4,	PHASE_A, 0},
    {IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_PWM_MODE,		PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_DISABLED,	ACP_INPUT_ADC2,	PHASE_C, 0},
    {IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_DISABLED, IN_PIN_PWM_MODE,		PHASE_LOW_SIDE,	PHASE_ACTIVE,	ACP_INPUT_ADC3,	PHASE_B, 0},
    {IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_DISABLED,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_PWM_MODE,		PHASE_LOW_SIDE,	PHASE_ACTIVE,	ACP_INPUT_ADC4,	PHASE_A, 0},
    {IN_PIN_PWM_MODE,		PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_DISABLED,	ACP_INPUT_ADC2,	PHASE_C, 0},
    {IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_DISABLED,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_DISABLED,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_DISABLED,	ACP_INPUT_ADC2,	PHASE_B, 0},
    {IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_ACTIVE,	ACP_INPUT_ADC2,	PHASE_B, 0}
};

static const BLDC_Rampup_Table_t BLDC_RampupTable[RAMPUP_STEPS] =
{
    {50, 100},
    {51, 90},
    {53, 80},
    {55, 70},
    {57, 60},
    {60, 50}
};

/*=============================================================================
=======                VARIABLES & MESSAGES & RESSOURCEN                =======
=============================================================================*/
static volatile bool bldc_ZeroCrossWindowOpen = false;

uint8_t bldc_PWMValue = 0;

static volatile uint8_t bldc_RampupStep = 0;	/* aktueller Ramp-Up Schritt */
static volatile uint8_t bldc_CommutationStep = 0;	/* aktueller Kommutierungsschritt */
static volatile uint8_t bldc_FailedCommutations[3] = {0,0,0}; /* Fehlerhafte Kommutierungen pro Phase */

uint16_t bldc_RPMSetpoint = 0;

static volatile uint16_t bldc_tCommutationDelay = 0; /* Berechnete Verzoegerung um 30° Phasenwinkel zu erreichen */
static volatile uint16_t bldc_tCommutation = UINT8_MAX;
static volatile uint16_t bldc_tZeroCross = UINT8_MAX;
static volatile uint16_t bldc_tZeroCrossWindowStart = UINT8_MAX;
static volatile uint16_t bldc_tZeroCrossWindowStop = UINT8_MAX;

static uint16_t bldc_revolutionTime = 0; /* Zaehlt die Zeit fuer eine Umdrehung (zur RPM Berechnung) */

volatile BLDC_Status_t bldc_Status = 
{
    .batVoltage = 0,
    .motorCurrent = 0,
    .RPMActual = 0,
    .curState = BLDC_STATE_STOP,
    .error = BLDC_NO_ERROR
};

static MAVG_FilterContent_t bldc_CurrentFilter[8];
static MAVG_FilterContent_t bldc_VoltageFilter[8];
static MAVG_FilterContent_t bldc_PPMFilter[8];
static MAVG_FilterData_t bldc_CurrentFilterData;
static MAVG_FilterData_t bldc_VoltageFilterData;
static MAVG_FilterData_t bldc_PPMFilterData;
static pidData_t bldc_PIDData;
extern BLDC_Config_t bldc_Config;

/*=============================================================================
=======                              METHODS                           =======
=============================================================================*/
static void bldc_SetCommutation(uint8_t commutationStep);
void bldc_Beep(uint16_t freq, uint16_t duration);
extern void bldc_ReadConfigData(void);
extern void bldc_WriteConfigData(void);
extern void bldc_StoreError(BLDC_Error_t error);

/* -----------------------------------------------------
* --               Public functions                  --
* ----------------------------------------------------- */

void BLDC_Init(void)
{
    wdt_enable(WDTO_500MS);

    /* DDR und status der Digitalausgänge einstellen */
    PORT_BLDC &= ~(_BV(PIN_PHASE_A_SD)|_BV(PIN_PHASE_B_SD)|_BV(PIN_PHASE_C_SD)|_BV(PIN_PHASE_A_IN)|_BV(PIN_PHASE_B_IN)|_BV(PIN_PHASE_C_IN));
    DDR_BLDC |= (_BV(DDRBIT_PHASE_A_IN)|_BV(DDRBIT_PHASE_B_IN)|_BV(DDRBIT_PHASE_C_IN)|_BV(DDRBIT_PHASE_A_SD)|_BV(DDRBIT_PHASE_B_SD)|_BV(DDRBIT_PHASE_C_SD));
        
    /* Resetgrund lesen und ggf. speichern */
    if ((MCUSR & WDRF) == WDRF)
    {
        /* Watchdog Reset */
        bldc_StoreError(BLDC_ERROR_WDG_RESET);
        MCUSR |= WDRF;
    }
    
    if ((MCUSR & WDRF) == BORF)
    {
        /* Brownout Reset */
        bldc_StoreError(BLDC_ERROR_BROWNOUT_RESET);
        MCUSR |= BORF;
    }

    bldc_CurrentFilterData.filterContent = bldc_CurrentFilter;
    bldc_VoltageFilterData.filterContent = bldc_VoltageFilter;
    bldc_PPMFilterData.filterContent = bldc_PPMFilter;

    MAVG_Init(&bldc_CurrentFilterData, 8, 0);
    MAVG_Init(&bldc_VoltageFilterData, 8, 0);
    MAVG_Init(&bldc_PPMFilterData, 3, 0);
    
    pid_Init(1, 1, 1, &bldc_PIDData);
    
    bldc_ReadConfigData();
}

void BLDC_Start(void)
{
    SVI_Start();
    PWM_Start(0);
    
    pid_Reset_Integrator(&bldc_PIDData);
    BLDC_StopMotor(false);
    
    wdt_reset();
    bldc_Beep(1000, 300);
    
    LED_Blink(BLDC_LED_BLINK_SLOW);
}

void BLDC_StartMotor(void)
{
    /* Motor muss erst mal stehen... */
    if (bldc_Status.curState == BLDC_STATE_STOP)
    {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            bldc_Status.curState = BLDC_STATE_ALIGN;
            bldc_RampupStep = 0;
        }
            
        /* Initialen PWM Wert setzen, Kommutierung bei 0 beginnen */
        PWM_SetValue(ALIGN_PWM);
        bldc_SetCommutation(0);
        TMR1_EnableTimerA(ALIGN_TIME);
        LED_Blink(BLDC_LED_BLINK_FAST);
    }
}

void BLDC_StopMotor(bool quickstop)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        if (true == quickstop)
        {
            bldc_SetCommutation(BLDC_COMMUTATION_QUICKSTOP);
        }
        else
        {
            bldc_SetCommutation(BLDC_COMMUTATION_OFF);
        }
        
        /* Alles stoppen */
        TMR1_DisableTimerA();
        TMR1_DisableTimerB();
        ACP_Disable();
        ADC_Enable();
        
        bldc_Status.curState = BLDC_STATE_STOP;
        bldc_CommutationStep = 0;
    }
}

void BLDC_Mainfunction(void)
{
    /* Spannung prüfen */
    /* Strom prüfen */
    /* PPM Sollwert holen */
    /* Motordrehzahl berechnen */
    
    bldc_Status.batVoltage = MAVG_GetResult(&bldc_VoltageFilterData);
    bldc_Status.motorCurrent = MAVG_GetResult(&bldc_CurrentFilterData);

    switch (bldc_Status.curState)
    {
        case BLDC_STATE_STOP:
        break;
        
        case BLDC_STATE_ALIGN:
        break;
        
        case BLDC_STATE_RAMP_UP:
        break;

        case BLDC_STATE_LAST_RAMP_UP:
        /* Regler initialisieren... */
        pid_Reset_Integrator(&bldc_PIDData);
        break;

        case BLDC_STATE_RUNNING:
        
        /* Regler, PWM Sollwertvorgabe */
        /*		bldc_PWMValue = pid_Controller(int16_t setPoint, int16_t processValue, struct PID_DATA *pid_st);*/
        PWM_SetValue(bldc_PWMValue);

        /*	Wenn 6 mal (3 Umdrehungen) auf einer Phase kein gültiger  Nulldurchgang, erfolgt Stopp */
        if ((bldc_FailedCommutations[0] >= 6) ||
        (bldc_FailedCommutations[1] >= 6) ||
        (bldc_FailedCommutations[2] >= 6))
        {
            BLDC_StopMotor(true);
            /* TODO: Fehler setzen */
        }
        break;

        default:
        /* Your code here */
        break;
    }
    
    wdt_reset();
}

/* -----------------------------------------------------
* --               Private functions                  --
* ----------------------------------------------------- */
void bldc_Beep(uint16_t freq, uint16_t duration)
{
    uint16_t ctr;
    if (BLDC_STATE_STOP == bldc_Status.curState)
    {
        PWM_Stop();
        PWM_SetFrequencyMode();
        PWM_SetValue(freq);
        PWM_Start(0);
        
        bldc_SetCommutation(0);
        for (ctr = 0; ctr < duration; ctr++)
        {
            _delay_ms(1);
        }
        bldc_SetCommutation(BLDC_COMMUTATION_OFF);
        
        PWM_Stop();
        PWM_SetDutyMode();
    }
}

void bldc_SetCommutation(uint8_t commutationStep)
{
    uint8_t ddrByte;
    uint8_t portByte;
    
    /* DDR der Pins entsprechend der aktuellen Kommutierung setzen (PWM pin als Eingang) */
    ddrByte = DDR_BLDC;
    ddrByte &= ~(_BV(DDRBIT_PHASE_A_IN)|_BV(DDRBIT_PHASE_B_IN)|_BV(DDRBIT_PHASE_C_IN));
    ddrByte |= _BV(BLDC_CommutationStates[commutationStep].phaseA_IN_DDR)|
    _BV(BLDC_CommutationStates[commutationStep].phaseB_IN_DDR)|
    _BV(BLDC_CommutationStates[commutationStep].phaseC_IN_DDR);
    
    /* Und Ausgänge entsprechend der Tabelle setzen */
    portByte = PORT_BLDC;
    portByte &= ~(_BV(PIN_PHASE_A_SD)|_BV(PIN_PHASE_B_SD)|_BV(PIN_PHASE_C_SD)|
    _BV(PIN_PHASE_A_IN)|_BV(PIN_PHASE_B_IN)|_BV(PIN_PHASE_C_IN));
    
    portByte |= _BV(BLDC_CommutationStates[commutationStep].phaseA_SD)|
    _BV(BLDC_CommutationStates[commutationStep].phaseB_SD)|
    _BV(BLDC_CommutationStates[commutationStep].phaseC_SD);
    
    portByte |= _BV(BLDC_CommutationStates[commutationStep].phaseA_IN)|
    _BV(BLDC_CommutationStates[commutationStep].phaseB_IN)|
    _BV(BLDC_CommutationStates[commutationStep].phaseC_IN);
    
    PORT_BLDC = portByte;
    DDR_BLDC = ddrByte;
}

/* -----------------------------------------------------
* --           Interrupt service routines            --
* ----------------------------------------------------- */

ISR(TIMER1_COMPA_vect)
{
    uint8_t newCommutation;
    uint32_t temp;
    
    switch (bldc_Status.curState)
    {
        case BLDC_STATE_STOP:
        /* Nichts zu tun */
        break;
        
        case BLDC_STATE_ALIGN:
        /* Align Timeout rum, in den Ramp Up Modus wechseln */
        bldc_Status.curState = BLDC_STATE_RAMP_UP;
        bldc_RampupStep = 0;
        
        /* Kommutierung einen Schritt weiterschalten und PWM aktivieren */
        PWM_SetValue(BLDC_RampupTable[bldc_RampupStep].pwmDuty);
        TMR1_EnableTimerA(BLDC_RampupTable[bldc_RampupStep].commutationTime);
        bldc_SetCommutation(1);
        break;

        case BLDC_STATE_RAMP_UP:
        /* Ein Ramp-Up increment ist abgelaufen, Kommutierung weiterschalten */
        newCommutation = bldc_CommutationStep++;
        newCommutation %= 6;
        
        /* Wenn alle Schritt abgelaufen sind, in den nächsten State wechseln */
        if (++bldc_RampupStep == (RAMPUP_STEPS - 1))
        {
            bldc_Status.curState = BLDC_STATE_LAST_RAMP_UP;
        }
        
        /* PWM sollwert setzen und Kommutierung aktivieren */
        PWM_SetValue(BLDC_RampupTable[bldc_RampupStep].pwmDuty);
        bldc_SetCommutation(newCommutation);
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            /* Zeitpunkt der Kommutierung merken (für Fensterberechung) */
            bldc_tCommutation = TMR1_GetTimerValue();
        }

        /* Und Kommutierungstimer für den nächsten Rampenschritt starten */
        TMR1_EnableTimerA(BLDC_RampupTable[bldc_RampupStep].commutationTime);
        break;

        case BLDC_STATE_LAST_RAMP_UP:
        /* Letzter Schritt in der Ramp-Up Phase. Kommutierung weiterschalten */
        newCommutation = bldc_CommutationStep++;
        newCommutation %= 6;
        
        /* Zähler für Kommutierungsfehler initialisieren */
        bldc_FailedCommutations[0] = 0;
        bldc_FailedCommutations[1] = 0;
        bldc_FailedCommutations[2] = 0;
        
        /* Fenster zum ersten erwarteten Nulldurchgang berechnen. */
        bldc_tCommutationDelay = BLDC_RampupTable[bldc_RampupStep].commutationTime / 2;
        bldc_tZeroCrossWindowStart = 10;
        bldc_tZeroCrossWindowStop = bldc_tCommutationDelay - 10;
        bldc_ZeroCrossWindowOpen = false;
        
        /* Neuer State: Running */
        bldc_Status.curState = BLDC_STATE_RUNNING;
        
        /* Kommutierung setzen */
        bldc_SetCommutation(newCommutation);
        
        /* Zeitpunkt der Kommutierung für Fensterberechung merken */
        bldc_tCommutation = TMR1_GetTimerValue();
        
        /* Fenster zum Nulldurchgang starten */
        TMR1_EnableTimerB(bldc_tZeroCrossWindowStart);
        
        LED_Off();
        break;

        case BLDC_STATE_RUNNING:
        /* Kommutierung weiterschalten */
        newCommutation = bldc_CommutationStep++;
        newCommutation %= 6;

        /* Fenster zum erwarteten Nulldurchgang berechnen:
        Fenster = Letzter Nulldurchgang+-10%??
        Wenn Nulldurchgang innerhalb dieses Fensters erfolgt,
        wird Commutationdelay(30°) neu berechnet (gütliger Nulldurchgang erkannt)
        Wenn nicht, erfolgt kommutierung mit letztem Phasenwinkel.
        */
        temp = bldc_tCommutationDelay * 100;
        temp += 500;
        temp /= 1000;
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            bldc_tZeroCrossWindowStart = bldc_tCommutationDelay - temp;
            bldc_tZeroCrossWindowStop = bldc_tZeroCrossWindowStart + (temp * 2);
        }
        
        /* Neue Kommutierung setzen */
        bldc_SetCommutation(newCommutation);
        bldc_tCommutation = TMR1_GetTimerValue();
        
        /* ADC starten */
        ADC_SelectInput(BLDC_ADC_CURRENT_INPUT);
        ADC_StartConversion();

        /* Fenster zum Nulldurchgang starten */
        TMR1_EnableTimerB(bldc_tZeroCrossWindowStart);
        break;

        default:
        /* Fehler: Motor stoppen */
        BLDC_StopMotor(true);
        /* TODO: Fehler setzen */
        break;
    }
}

ISR(TIMER1_COMPB_vect)
{
    /* Wenn der Timer abläuft, während wir auf einen Nulldurchgang warten (Fenster offen)... */
    if (true == bldc_ZeroCrossWindowOpen)
    {
        /* ...wurde innerhalb des Fensters kein gültiger Nulldurchgang erkannt.
                    Fehlerzähler für die aktuelle Phase inkrementieren. */
        bldc_FailedCommutations[BLDC_CommutationStates[bldc_CommutationStep].BEMFPhase]++;
        bldc_ZeroCrossWindowOpen = false;

        /* Analogkomparator ausschalten und ADC (Strom- u. Spannungsmessung) einschalten */
        ACP_Disable();
        ADC_Enable();

        /* ADC starten */
        ADC_SelectInput(BLDC_ADC_VOLTAGE_INPUT);
        ADC_StartConversion();

        /* Fenster-timer stoppen, Kommutierungstimer mit letzter Kommutierungszeit starten */
        TMR1_DisableTimerB();
        TMR1_EnableTimerA(bldc_tCommutationDelay);
    }
    else /* Das Fenster ist noch geschlossen, d.h. jetzt öffnen... */
    {
        /* ADC Ausschalten, Komparatoreingang auf floatende Phase einstellen und einschalten */
        ADC_Disable();
        ACP_SelectInput(BLDC_CommutationStates[bldc_CommutationStep].ComparatorInput);
        ACP_Enable();
        bldc_ZeroCrossWindowOpen = true;
        
        /* Timer zum schliessen des Fensters starten */
        TMR1_EnableTimerB(bldc_tZeroCrossWindowStop);
    }
}

ISR(ANALOG_COMP_vect)
{
    /* Analogkomparator hat einen Nulldurchgang erkannt */
    if ((BLDC_STATE_LAST_RAMP_UP == bldc_Status.curState) ||
    (BLDC_STATE_RUNNING == bldc_Status.curState))
    {
        /* Zeitpunkt des Nulldurchgangs speichern */
        bldc_tZeroCross = TMR1_GetTimerValue();
        
        /* Fenstertimer stoppen, Komparator ausschalten, ADC einschalten */
        TMR1_DisableTimerB();
        ACP_Disable();
        ADC_Enable();
        bldc_ZeroCrossWindowOpen = false;

        /* ADC starten */
        ADC_SelectInput(BLDC_ADC_VOLTAGE_INPUT);
        ADC_StartConversion();
        
        /*
        * Berechnung CommutationDelay: tDelay = tCommutation + (tZeroCross * 2)
        * tDelay = Zeit vom aktuellen Nulldurchgang bis zur nächsten Kommutierung
        * tZeroCross = Zeitpunkt des aktuellen Nulldurchgangs
        * tCommutation = Zeitpunkt der aktuellen Kommutierung
        */
        bldc_tCommutationDelay = bldc_tZeroCross - bldc_tCommutation;
        bldc_FailedCommutations[BLDC_CommutationStates[bldc_CommutationStep].BEMFPhase] = 0;
        
        /* Zeit für eine komplette Umdrehung aus der Zeit für eine Drehung um 30° Berechnen
         * (360° = 30° * 12) 
         */
        bldc_revolutionTime = bldc_tCommutationDelay * 12;
        
        /* Timer für nächste Kommutierung mit dem neu berechneten Zeitpunkt starten */
        TMR1_EnableTimerA(bldc_tCommutationDelay);
    }
}

ISR(ADC_vect)
{
    uint16_t adValue;
    ADC_Input_t adcInput;
    adValue = ADC_GetConversionResult();
    adcInput = ADC_GetSelectedInput();
    
    if (BLDC_ADC_CURRENT_INPUT == adcInput)
    {
        MAVG_AddValue(&bldc_CurrentFilterData, adValue);
    }
    else if (BLDC_ADC_VOLTAGE_INPUT == adcInput)
    {
        MAVG_AddValue(&bldc_VoltageFilterData, adValue);        
    }
    else
    {
        /* Nichts zu tun */
    }
}
