/*!
***     \file	  H_File1.c
***     \ingroup  H File1
***     \author   Daniel
***     \date	  11/23/2014 2:02:31 PM
***     \brief    TODO
***
******************************************************************************/

/* Header file guard symbol to prevent multiple includes */
#ifndef H_File1_H_
#define H_File1_H_

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
typedef uint16_t MAVG_FilterContent_t;
typedef uint16_t* MAVG_FilterContentPtr_t;

typedef struct MAVG_FilterData_s
{
	uint8_t filterLen;
	uint8_t filterPos;
	MAVG_FilterContentPtr_t filterContent;
}MAVG_FilterData_t;

/*=============================================================================
=======                              EXPORTS                            =======
=============================================================================*/
void MAVG_Init(MAVG_FilterData_t *filterData, uint8_t filterLen, uint16_t initValue);
void MAVG_AddValue(MAVG_FilterData_t *filterData, uint16_t value);
uint16_t MAVG_GetResult(MAVG_FilterData_t *filterData);

/* end of storage class specifier if used with C++ */
#ifdef  __cplusplus
}
#endif

#endif /*H_File1_H_*/
