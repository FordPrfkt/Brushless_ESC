/*!
***     \file	  PID_Controller.c
***     \ingroup  PID_Controller
***     \author   Daniel
***     \date	  9/19/2015 12:42:22 PM
***     \brief    PID Implementation taken from Atmel AVR221
***
******************************************************************************/

/* Header file guard symbol to prevent multiple includes */
#ifndef PID_Controller_H_
#define PID_Controller_H_

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
#define SCALING_FACTOR  128
/*! \brief Maximum values
 *
 * Needed to avoid sign/overflow problems
 */
// Maximum value of variables
#define MAX_INT         INT16_MAX
#define MAX_LONG        INT32_MAX
#define MAX_I_TERM      (MAX_LONG / 2)

/*=============================================================================
=======                       CONSTANTS  &  TYPES                       =======
=============================================================================*/
/*! \brief PID Status
 *
 * Setpoints and data used by the PID control algorithm
 */
typedef struct PID_DATA{
  //! Last process value, used to find derivative of process value.
  int16_t lastProcessValue;
  //! Summation of errors, used for integrate calculations
  int32_t sumError;
  //! The Proportional tuning constant, multiplied with SCALING_FACTOR
  int16_t P_Factor;
  //! The Integral tuning constant, multiplied with SCALING_FACTOR
  int16_t I_Factor;
  //! The Derivative tuning constant, multiplied with SCALING_FACTOR
  int16_t D_Factor;
  //! Maximum allowed error, avoid overflow
  int16_t maxError;
  //! Maximum allowed sumerror, avoid overflow
  int32_t maxSumError;
} pidData_t;

/*=============================================================================
=======                              EXPORTS                            =======
=============================================================================*/
void pid_Init(int16_t p_factor, int16_t i_factor, int16_t d_factor, struct PID_DATA *pid);
int16_t pid_Controller(int16_t setPoint, int16_t processValue, struct PID_DATA *pid_st);
void pid_Reset_Integrator(pidData_t *pid_st);

/* end of storage class specifier if used with C++ */
#ifdef  __cplusplus
}
#endif

#endif /*PID_Controller_H_*/
