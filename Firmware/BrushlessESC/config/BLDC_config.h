/*
 * BLDC_config.h
 *
 * Created: 07.10.2015 00:40:02
 *  Author: Daniel
 */ 
#ifndef BLDC_CONFIG_H_
#define BLDC_CONFIG_H_

/* Motor Parameters */
#define MOTOR_RPM_CONSTANT 950 /* Emax Outrunner BL2215/25 950 RPM/V */
#define MOTOR_RPM_MAX 10545 /* 950 RPM/V x 11.1V */

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

#define BLDC_ERROR_ID 0x40

/************************************************************************/
/* Port+Pin Einstellungen                                               */
/************************************************************************/ 
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

/* ADC Eingänge */
#define BLDC_ADC_CURRENT_INPUT ADC_INPUT_ADC1
#define BLDC_ADC_VOLTAGE_INPUT ADC_INPUT_ADC7

#endif /* BLDC_CONFIG_H_ */
