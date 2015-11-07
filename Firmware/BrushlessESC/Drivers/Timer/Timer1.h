/*!
***     \file	  ICP.c
***     \ingroup  ICP
***     \author   Daniel
***     \date	  9/20/2015 2:42:12 AM
***     \brief    TODO
***
******************************************************************************/

/* Header file guard symbol to prevent multiple includes */
#ifndef ICP_H_
#define ICP_H_

/* storage class specifier if used with C++ */
#ifdef  __cplusplus
  extern "C" {
#endif

/*=============================================================================
=======                            INCLUDES                             =======
=============================================================================*/

/*=============================================================================
=======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
=============================================================================*/

/*=============================================================================
=======                       CONSTANTS  &  TYPES                       =======
=============================================================================*/
typedef enum TMR1_Prescaler_e
{
    TMR1_PRESCALER_1 = _BV(CS10),
    TMR1_PRESCALER_8 = _BV(CS11),
    TMR1_PRESCALER_32 = _BV(CS10)|_BV(CS11),
    TMR1_PRESCALER_64 = _BV(CS12),
    TMR1_PRESCALER_128 = _BV(CS12)|_BV(CS10),
    TMR1_PRESCALER_256 = _BV(CS12)|_BV(CS11),
    TMR1_PRESCALER_1024 = _BV(CS12)|_BV(CS11)|_BV(CS10)
}TMR1_Prescaler_t;

/*=============================================================================
=======                              EXPORTS                            =======
=============================================================================*/
void TMR1_Init(TMR1_Prescaler_t prescaler);
void TMR1_EnableTimerA(uint16_t timerVal);
void TMR1_DisableTimerA(void);
void TMR1_EnableTimerB(uint16_t timerVal);
void TMR1_DisableTimerB(void);
uint16_t TMR1_GetTimerValue(void);
void TMR1_EnableICP(void);
void TMR1_DisableICP(void);
uint32_t TMR1_Ticks2us(uint32_t ticks);
uint32_t TMR1_us2Ticks(uint16_t us);
uint32_t TMR1_Ticks2ns(uint32_t ticks);
uint32_t TMR1_ns2Ticks(uint32_t ns);

/* end of storage class specifier if used with C++ */
#ifdef  __cplusplus
}
#endif

#endif /*ICP_H_*/
/* EOF */