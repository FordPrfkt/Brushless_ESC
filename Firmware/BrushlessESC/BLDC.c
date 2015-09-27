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
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "drivers/ACP/ACP.h"
#include "drivers/ADC/ADC.h"
#include "drivers/ICP/ICP.h"
#include "drivers/PWM/PWM.h"
#include "drivers/SPI/SPI_slave.h"
#include "BLDC.h"
/*=============================================================================
 =======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
 =============================================================================*/
/* Motor Parameters */
#define MOTOR_RPM_CONSTANT 950 /* Emax Outrunner BL2215/25 950 RPM/V */
#define MOTOR_RPM_MAX 10545 /* 950 RPM/V x 11.1V */

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

/* Port+Pin Einstellungen */
#define DDR_BLDC DDRD
#define DDRBIT_PHASE_A_IN DDD5
#define DDRBIT_PHASE_B_IN DDD4
#define DDRBIT_PHASE_C_IN DDD1
#define DDRBIT_PHASE_A_SD DDD7
#define DDRBIT_PHASE_B_SD DDD2
#define DDRBIT_PHASE_C_SD DDD0
#define PORT_BLDC PORTD
#define PIN_PHASE_A_IN PORTD5
#define PIN_PHASE_B_IN PORTD4
#define PIN_PHASE_C_IN PORTD1
#define PIN_PHASE_A_SD PORTD7
#define PIN_PHASE_B_SD PORTD2
#define PIN_PHASE_C_SD PORTD0

/* Align Parameters */
#define ALIGN_PWM 50
#define ALIGN_TIME 1000

/* Rampup Parameters */
#define RAMPUP_RPM_1 (MOTOR_RPM_MAX / 60)
#define RAMPUP_RPM_2 (MOTOR_RPM_MAX / 6)
#define RAMPUP_PWM_DUTY1 50
#define RAMPUP_PWM_DUTY2 60
#define RAMPUP_STEPS 6

#define PWM_MIN 10
#define PWM_MAX 200
/*=============================================================================
 =======                       CONSTANTS  &  TYPES                       =======
 =============================================================================*/
typedef enum BLDC_ZeroCrossWindowState_e
{
	BLDC_ZCROSS_WINDOWCLOSED = 0,
	BLDC_ZCROSS_WINDOWOPEN
}BLDC_ZeroCrossWindowState_t;

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
	uint16_t ComparatorInput:3;
	uint16_t BEMFPhase:2;
	uint16_t unused:2;
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
static uint8_t bldc_PWMValue = 0;

static volatile uint8_t bldc_RampupStep = 0;	/* aktueller Ramp-Up Schritt */
static volatile uint8_t bldc_CommutationStep = 0;	/* aktueller Kommutierungsschritt */
static volatile uint8_t bldc_FailedCommutations[3] = {0,0,0}; /* Fehlerhafte Kommutierungen pro Phase */

static volatile uint16_t bldc_tCommutationDelay = 0; /* Berechnete Verzoegerung um 30° Phasenwinkel zu erreichen */
static volatile uint16_t bldc_tCommutation = UINT8_MAX;
static volatile uint16_t bldc_tZeroCross = UINT8_MAX;
static volatile uint16_t bldc_tZeroCrossWindowStart = UINT8_MAX;
static volatile uint16_t bldc_tZeroCrossWindowStop = UINT8_MAX;

static uint16_t bldc_motorCurrent = 0;
static uint16_t bldc_batVoltage = 0;

static uint16_t bldc_RPMSetpopint = 0;
static uint16_t bldc_RPMActual = 0;
static uint16_t bldc_revolutionTimeCtr = 0; /* Zaehlt die Zeit fuer eine Umdrehung (zur RPM Berechnung) */

static volatile BLDC_State_t bldc_State = BLDC_STATE_STOP;
static volatile BLDC_ZeroCrossWindowState_t bldc_ZeroCrossDetectionState = BLDC_ZCROSS_WINDOWCLOSED;
static volatile BLDC_Error_t bldc_ErrorStatus = BLDC_NO_ERROR;
/*=============================================================================
 =======                              METHODS                           =======
 =============================================================================*/
static uint16_t bldc_GetTimer1Value(void);
static void bldc_EnableTimer1A(uint16_t timerVal);
static void bldc_DisableTimer1A(void);
static void bldc_EnableTimer1B(uint16_t timerVal);
static void bldc_DisableTimer1B(void);
/* -----------------------------------------------------
 * --               Public functions                  --
 * ----------------------------------------------------- */
void BLDC_Init(void)
{
	PORT_BLDC &= ~(_BV(PIN_PHASE_A_SD)|_BV(PIN_PHASE_B_SD)|_BV(PIN_PHASE_C_SD)|_BV(PIN_PHASE_A_IN)|_BV(PIN_PHASE_B_IN)|_BV(PIN_PHASE_C_IN));
	DDR_BLDC |= (_BV(DDRBIT_PHASE_A_IN)|_BV(DDRBIT_PHASE_B_IN)|_BV(DDRBIT_PHASE_C_IN)|_BV(DDRBIT_PHASE_A_SD)|_BV(DDRBIT_PHASE_B_SD)|_BV(DDRBIT_PHASE_C_SD));
}

void BLDC_Start(void)
{
	ICP_Start();
	PWM_Start(0);	
}

void BLDC_StartMotor(void)
{
	bldc_State = BLDC_STATE_ALIGN;
	bldc_RampupStep = 0;
}

void BLDC_StateMachine(void)
{
	/* Spannung prüfen */
	/* Strom prüfen */
	/* PPM Sollwert holen */
	/* SPI Kommandos prüfen */
	
	switch (bldc_State)
	{
		case BLDC_STATE_STOP:
		case BLDC_STATE_ALIGN:
			/* Nichts zu tun */
		break;

		case BLDC_STATE_RAMP_UP:
		/* Your code here */
		break;

		case BLDC_STATE_LAST_RAMP_UP:
		/* Regler initialisieren... */
		break;

		case BLDC_STATE_RUNNING:
		/* Regler, PWM Sollwertvorgabe */
		PWM_SetValue(bldc_PWMValue);

		/*	Wenn 6 mal (3 Umdrehungen) auf einer Phase kein gültiger 
		    Nulldurchgang, erfolgt Stopp */
		if ((bldc_FailedCommutations[0] >= 6) ||
		(bldc_FailedCommutations[1] >= 6) ||
		(bldc_FailedCommutations[2] >= 6))
		{
			bldc_StopMotor(true);
			/* TODO: Fehler setzen */
		}
		break;

		default:
		/* Your code here */
		break;
	}
}

/* -----------------------------------------------------
 * --               Private functions                  --
 * ----------------------------------------------------- */
void bldc_EnableTimer1A(uint16_t timerVal)
{
	uint16_t temp = 0;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		temp = TCNT1;
		temp += timerVal;
		OCR1A = temp;
	}
	TIMSK1 |= _BV(OCIE1A);
}

void bldc_DisableTimer1A(void)
{
	TIMSK1 &= ~_BV(OCIE1A);
}

void bldc_EnableTimer1B(uint16_t timerVal)
{
	uint16_t temp;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		temp = TCNT1;
		temp += timerVal;
		OCR1B = temp;
	}	
	TIMSK1 |= _BV(OCIE1B);
}

void bldc_DisableTimer1B(void)
{
	TIMSK1 &= ~_BV(OCIE1B);	
}

uint16_t bldc_GetTimer1Value(void)
{
	uint16_t result;
	
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		result = TCNT1;
	}	
	
	return result;
}

void bldc_SetCommutation(uint8_t commutationStep)
{
	uint8_t ddrByte;
	uint8_t portByte;
	
	ddrByte = DDR_BLDC;
	ddrByte &= ~(_BV(DDRBIT_PHASE_A_IN)|_BV(DDRBIT_PHASE_B_IN)|_BV(DDRBIT_PHASE_C_IN));
	ddrByte |= _BV(BLDC_CommutationStates[commutationStep].phaseA_IN_DDR)|
				_BV(BLDC_CommutationStates[commutationStep].phaseB_IN_DDR)|
				_BV(BLDC_CommutationStates[commutationStep].phaseC_IN_DDR);
	
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

void bldc_StopMotor(bool quickstop)
{
	if (true == quickstop)
	{
		bldc_SetCommutation(BLDC_COMMUTATION_QUICKSTOP);
	}
	else
	{
		bldc_SetCommutation(BLDC_COMMUTATION_OFF);
	}
	
	bldc_State = BLDC_STATE_STOP;
	/* Reset Timer */
}

void bldc_AlignMotor(void)
{
	bldc_SetCommutation(0);
	bldc_EnableTimer1A(ALIGN_TIME);
}

bool SPI_Cmd_Callback(uint8_t cmd, volatile uint8_t *param, uint8_t paramLen)
{
	return false;
}

ISR(TIMER1_COMPA_vect)
{
	uint8_t newCommutation;
	uint32_t temp;
	switch (bldc_State)
	{
		case BLDC_STATE_STOP:
		/* Nichts zu tun */
		break;
		
		case BLDC_STATE_ALIGN:
			/* Align Timeout rum, in den Ramp Up Modus wechseln */
			bldc_State = BLDC_STATE_RAMP_UP;
			bldc_RampupStep = 0;
			bldc_SetCommutation(1);
			PWM_SetValue(BLDC_RampupTable[bldc_RampupStep].pwmDuty);
			bldc_EnableTimer1A(BLDC_RampupTable[bldc_RampupStep].commutationTime);
		break;

		case BLDC_STATE_RAMP_UP:
			/* Ein Ramp-Up increment ist abgelaufen, Kommutierung weiterschalten */
			if (++bldc_RampupStep == (RAMPUP_STEPS - 1))
			{
				bldc_State = BLDC_STATE_LAST_RAMP_UP;
			}

			newCommutation = bldc_CommutationStep++;
			newCommutation %= 6;
			
			PWM_SetValue(BLDC_RampupTable[bldc_RampupStep].pwmDuty);
			bldc_SetCommutation(newCommutation);
			bldc_tCommutation = bldc_GetTimer1Value();
			bldc_EnableTimer1A(BLDC_RampupTable[bldc_RampupStep].commutationTime);
		break;

		case BLDC_STATE_LAST_RAMP_UP:
			newCommutation = bldc_CommutationStep++;
			newCommutation %= 6;			
			bldc_SetCommutation(newCommutation);
			bldc_tCommutation = bldc_GetTimer1Value();
			
			bldc_FailedCommutations[0] = 0;
			bldc_FailedCommutations[1] = 0;
			bldc_FailedCommutations[2] = 0;
			
			/* Fenster zum erwarteten Nulldurchgang berechnen:
			   Fenster = Letzter Nulldurchgang+-10%?? 
			*/		
			bldc_tCommutationDelay = BLDC_RampupTable[bldc_RampupStep].commutationTime / 2;
			bldc_tZeroCrossWindowStart = 10;
			bldc_tZeroCrossWindowStop = bldc_tCommutationDelay - 10;
			bldc_EnableTimer1B(bldc_tZeroCrossWindowStart);
			bldc_State = BLDC_STATE_RUNNING;
		break;

		case BLDC_STATE_RUNNING:			
			newCommutation = bldc_CommutationStep++;
			newCommutation %= 6;

			bldc_SetCommutation(newCommutation);
			bldc_tCommutation = bldc_GetTimer1Value();

			/* Fenster zum erwarteten Nulldurchgang berechnen:
			   Fenster = Letzter Nulldurchgang+-10%?? 
			   Wenn Nulldurchgang innerhalb dieses Fensters erfolgt,
	           wird Commutationdelay(30°) neu berechnet (gütliger Nulldurchgang erkannt)
	           Wenn nicht, erfolgt kommutierung mit letztem Phasenwinkel.
			*/
			temp = bldc_tCommutationDelay * 100;
			temp += 500;
			temp /= 1000;
			bldc_tZeroCrossWindowStart = bldc_tCommutationDelay - temp;
			bldc_tZeroCrossWindowStop = bldc_tZeroCrossWindowStart + (temp * 2);
			bldc_EnableTimer1B(bldc_tZeroCrossWindowStart);				
		break;

		default:
			bldc_StopMotor(true);
			/* TODO: Fehler setzen */
		break;
	}	
}

ISR(TIMER1_COMPB_vect)
{
	switch (bldc_ZeroCrossDetectionState)
	{
		case BLDC_ZCROSS_WINDOWCLOSED:
			ADC_Disable();
			ACP_SelectInput(BLDC_CommutationStates[bldc_CommutationStep].ComparatorInput);
			ACP_Enable();
			bldc_ZeroCrossDetectionState = BLDC_ZCROSS_WINDOWOPEN;
			bldc_EnableTimer1B(bldc_tZeroCrossWindowStop);
		break;
		
		case BLDC_ZCROSS_WINDOWOPEN:
			ACP_Disable();
			ADC_Enable();
			bldc_DisableTimer1B();
			bldc_ZeroCrossDetectionState = BLDC_ZCROSS_WINDOWCLOSED;
			bldc_FailedCommutations[BLDC_CommutationStates[bldc_CommutationStep].BEMFPhase]++;
			bldc_EnableTimer1A(bldc_tCommutationDelay);
		break;
		
		default:
		break;
	}
}

ISR(ANALOG_COMP_vect)
{
	if ((BLDC_STATE_LAST_RAMP_UP == bldc_State) || 
		(BLDC_STATE_RUNNING == bldc_State))
	{
		/*
		 * Berechnung CommutationDelay: tDelay = tCommutation + (tZeroCross * 2)
		 * tDelay = Zeit vom aktuellen Nulldurchgang bis zur nächsten Kommutierung
		 * tZeroCross = Zeitpunkt des aktuellen Nulldurchgangs
		 * tCommutation = Zeitpunkt der aktuellen Kommutierung
		*/
		bldc_tZeroCross = bldc_GetTimer1Value();
		ACP_Disable();
		ADC_Enable();
		bldc_DisableTimer1B();
		bldc_ZeroCrossDetectionState = BLDC_ZCROSS_WINDOWCLOSED;
		
		bldc_tCommutationDelay = bldc_tZeroCross - bldc_tCommutation;
		bldc_FailedCommutations[BLDC_CommutationStates[bldc_CommutationStep].BEMFPhase] = 0;
		bldc_EnableTimer1A(bldc_tCommutationDelay);
	}
}

ISR(ADC_vect)
{
	
}
