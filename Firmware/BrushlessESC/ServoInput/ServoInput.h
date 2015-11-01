/*
 * Servo_Input.h
 *
 * Created: 07.10.2015 01:22:35
 *  Author: Daniel
 */ 


#ifndef SERVO_INPUT_H_
#define SERVO_INPUT_H_

#define SV_MAX_INVALID_PULSES 3
#define SV_NO_PULSE UINT16_MAX
#define SV_PULSE_MAX 10
#define SV_PULSE_MIN 1

void SVI_Init(void);
void SVI_Start(void);
void SVI_Stop(void);
uint16_t SVI_GetPulseDuration(void);

#endif /* SERVO_INPUT_H_ */

/* EOF */