/*!
***     \file	  SpeedController.c
***     \ingroup  SpeedController
***     \author   Daniel
***     \date	  9/19/2015 12:40:04 PM
***     \brief    TODO
***
******************************************************************************/

/*=============================================================================
 =======                            INCLUDES                             =======
 =============================================================================*/
#include "SpeedController.h"
/*=============================================================================
 =======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
 =============================================================================*/
#define IN_PIN_PWM_MODE 0
#define IN_PIN_CONSTANT_MODE 1
#define PHASE_LOW_SIDE 0
#define PHASE_HIGH_SIDE 1
#define PHASE_DISABLED 1
#define PHASE_ACTIVE 0

#define BLDC_COMMUTATION_OFF 6
#define BLDC_COMMUTATION_QUICKSTOP 7
#define BLDC_COMMUTATION_ALIGN 8

#define DDR_BLDC DDRD
#define DDRBIT_PHASE_A_IN DDD0
#define DDRBIT_PHASE_B_IN 
#define DDRBIT_PHASE_C_IN
#define DDRBIT_PHASE_A_SD DDD0
#define DDRBIT_PHASE_B_SD
#define DDRBIT_PHASE_C_SD

#define PORT_BLDC PORTD
#define PIN_PHASE_A_IN PORTD0
#define PIN_PHASE_B_IN
#define PIN_PHASE_C_IN
#define PIN_PHASE_A_SD PORTD0
#define PIN_PHASE_B_SD
#define PIN_PHASE_C_SD

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
	uint16_t ComparatorInput:3;
	uint16_t unused:4;
}BLDC_CommutationState_t;

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
static const BLDC_CommutationState_t BLDC_CommutationStates[9] = 
{
/* PhaseA_IN_DDR		phaseA_IN		phaseA_SD		PhaseB_IN_DDR			phaseB_IN		phaseB_SD		PhaseC_IN_DDR			phaseC_IN		phaseC_SD		Comparator */
{IN_PIN_PWM_MODE,		PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_DISABLED, IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_ACTIVE,	ACP_INPUT_ADC3,0},
{IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_DISABLED,	IN_PIN_PWM_MODE,		PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_ACTIVE,	ACP_INPUT_ADC4,0},
{IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_PWM_MODE,		PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_DISABLED,	ACP_INPUT_ADC2,0},
{IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_DISABLED, IN_PIN_PWM_MODE,		PHASE_LOW_SIDE,	PHASE_ACTIVE,	ACP_INPUT_ADC3,0},
{IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_DISABLED,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_PWM_MODE,		PHASE_LOW_SIDE,	PHASE_ACTIVE,	ACP_INPUT_ADC4,0},
{IN_PIN_PWM_MODE,		PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_DISABLED,	ACP_INPUT_ADC2,0}
{IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_DISABLED,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_DISABLED,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_DISABLED,	ACP_INPUT_ADC2,0}
{IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_ACTIVE,	ACP_INPUT_ADC2,0}
{IN_PIN_CONSTANT_MODE,	PHASE_HIGH_SIDE,PHASE_ACTIVE,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_ACTIVE,	IN_PIN_CONSTANT_MODE,	PHASE_LOW_SIDE,	PHASE_ACTIVE,	ACP_INPUT_ADC2,0}
};

/*=============================================================================
 =======                VARIABLES & MESSAGES & RESSOURCEN                =======
 =============================================================================*/
static uint8_t bldc_CommutationStep = 0;	/* aktueller Kommutierungsschritt */
static uint8_t bldc_CommutationDelayTime = 0; /* Berechnete Verzoegerung um 30° Phasenwinkel zu erreichen */
static uint8_t bldc_FailedCommutations[3] = {0,0,0}; /* Fehlerhafte Kommutierungen pro Phase */
	
static uint16_t bldc_motorCurrent = 0;
static uint16_t bldc_batVoltage = 0;
static uint16_t bldc_RPMSetpopint = 0;
static uint16_t bldc_RPMActual = 0;
static BLDC_State_t bldc_State = BLDC_STATE_STOP;
/*=============================================================================
 =======                              METHODS                           =======
 ========================================PORTD=====================================*/

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
			/* Nichts zu tun */
		break;
		
		case BLDC_STATE_ALIGN:
			bldc_AlignMotor();
		break;

		case BLDC_STATE_RAMP_UP:
		/* Your code here */
		break;

		case BLDC_STATE_LAST_RAMP_UP:
		/* Regler initialisieren... */
		break;

		case BLDC_STATE_RUNNING:
		/* Regler, PWM Sollwertvorgabe */
		break;

		default:
		/* Your code here */
		break;
	}
}

/* -----------------------------------------------------
 * --               Private functions                  --
 * ----------------------------------------------------- */
void bldc_StartDelayTimer(uint16_t delayTime)
{
	
}
	/* Fenster zum erwarteten Nulldurchgang berechnen
	Fenster = Letzter Nulldurchgang+-10%??
	Wenn Nulldurchgang innerhalb dieses Fensters erfolgt,
	wird Commutationdelay(30°) neu berechnet (gütliger Nulldurchgang erkannt)
	Wenn nicht, erfolgt kommutierung mit letzem Phasenwinkel.
	Wenn 6 mal (3 Umdrehungen) auf einer Phase kein gültiger Nulldurchgang, erfolgt notstopp 
	
	Berechnung CommutationDelay: tDelay = tCommutation + (tZeroCross * 2)
	tDelay = Zeit von der aktuellen Kommutierung bis zur nächsten Kommutierung
	tZeroCross = Zeit vom der aktuellen Kommutierung bis zum aktuellen Nulldurchgang
	tCommutation = Zeitpunkt der aktuellen Kommutierung
	*/

void bldc_SetCommutation(uint8_t commutationStep, bool startTimer)
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
		
	/* ACP Erst am Anfang des zulässigen Fensters aktivieren */
	if (true == startTimer)
	{
		bldc_StartDelayTimer(BLDC_BEMF_ZEROCROSS_WINDOW_START);		
	}
}

void bldc_StopMotor(bool quickstop)
{
	if (TRUE == quickstop)
	{
		bldc_SetCommutation(BLDC_COMMUTATION_QUICKSTOP, false);
	}
	else
	{
		bldc_SetCommutation(BLDC_COMMUTATION_OFF, false);
	}
	
	bldc_State = BLDC_STATE_STOP;
	/* Reset Timer */
}

void bldc_AlignMotor(void)
{
	bldc_SetCommutation(BLDC_COMMUTATION_ALIGN, false);
	bldc_StartDelayTimer(BLDC_ALIGN_TIME);
}

ISR(TIMER0_COMPA_vect)
{
	uint8_t newCommutation;
	switch (bldc_State)
	{
		case BLDC_STATE_STOP:
		/* Nichts zu tun */
		break;
		
		case BLDC_STATE_ALIGN:
			/* Align Timeout rum, in den Ramp Up Modus wechseln */
			bldc_State = BLDC_STATE_RAMP_UP;
			rampUpTimer = RAMP_UP_INIT;
			bldc_SetCommutation(1, false);
			bldc_StartDelayTimer(rampUpTimer);
		break;

		case BLDC_STATE_RAMP_UP:
			/* Ein Ramp-Up increment ist abgelaufen, Kommutierung weiterschalten */
			newCommutation = bldc_CommutationStep++;
			newCommutation %= 6;
			rampUpTimer += RAMP_UP_RATE;
			if (rampUpTimer == MAX_RAMP_UP)
			{
				bldc_State = BLDC_STATE_LAST_RAMP_UP;
			}
			bldc_SetCommutation(newCommutation, false);
			bldc_StartZeroCrossWindow();
			bldc_StartDelayTimer(rampUpTimer);
		break;

		case BLDC_STATE_LAST_RAMP_UP:
		
		break;

		case BLDC_STATE_RUNNING:
		
		break;

		default:
			bldc_StopMotor(true);
			/* TODO: Fehler setzen */
		break;
	}	
}

ISR(TIMER0_COMPB_vect)
{
	switch (bldc_ZeroCrossDetectionState)
	{
		case BLDC_ZCROSS_WINDOWCLOSED:
			bldc_ArmZeroCrossDetection();
		break;
		
		case BLDC_ZCROSS_WINDOWOPEN:
			bldc_DisarmZeroCrossDetection();
		break;
		
		default:
		break;
	}
}
