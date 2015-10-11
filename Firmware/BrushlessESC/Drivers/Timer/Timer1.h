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

/*=============================================================================
=======                              EXPORTS                            =======
=============================================================================*/
void TMR1_Init(uint8_t prescaler);
void TMR1_EnableTimerA(uint16_t timerVal);
void TMR1_DisableTimerA(void);
void TMR1_EnableTimerB(uint16_t timerVal);
void TMR1_DisableTimerB(void);
uint16_t TMR1_GetTimerValue(void);
void TMR1_EnableICP(void);
void TMR1_DisableICP(void);

/* end of storage class specifier if used with C++ */
#ifdef  __cplusplus
}
#endif

#endif /*ICP_H_*/
