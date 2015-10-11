/*
 * Servo_Input.h
 *
 * Created: 07.10.2015 01:22:35
 *  Author: Daniel
 */ 


#ifndef SERVO_INPUT_H_
#define SERVO_INPUT_H_

void SVI_Init(void);
void SVI_Start(void);
void SVI_Stop(void);
uint16_t SVI_GetPulseWidth(void);

#endif /* SERVO_INPUT_H_ */