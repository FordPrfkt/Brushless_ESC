/*!
***     \file	  C_File1.c
***     \ingroup  C File1
***     \author   Daniel
***     \date	  11/23/2014 2:02:25 PM
***     \brief    TODO
***
******************************************************************************/

/*=============================================================================
 =======                            INCLUDES                             =======
 =============================================================================*/
#include <stdint.h>
#include <stdbool.h>
#include "MovingAvgFilter.h"
/*=============================================================================
 =======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
 =============================================================================*/

/*=============================================================================
 =======                       CONSTANTS  &  TYPES                       =======
 =============================================================================*/

/*=============================================================================
 =======                VARIABLES & MESSAGES & RESSOURCEN                =======
 =============================================================================*/

/*=============================================================================
 =======                              METHODS                           =======
 =============================================================================*/

/* -----------------------------------------------------
 * --               Public functions                  --
 * ----------------------------------------------------- */
void MAVG_Init(MAVG_FilterData_t *filterData, uint8_t filterLen, uint16_t initValue)
{
	uint8_t ctr;
	filterData->filterLen = filterLen;
	filterData->filterPos = 0;

	for (ctr = 0; ctr < filterLen; ctr++)
	{
		filterData->filterContent[ctr] = initValue;
	}
}

void MAVG_AddValue(MAVG_FilterData_t *filterData, uint16_t value)
{
	filterData->filterPos++;
	filterData->filterPos %= filterData->filterLen;
	filterData->filterContent[filterData->filterPos] = value;
}

uint16_t MAVG_GetResult(MAVG_FilterData_t *filterData)
{
	uint8_t ctr;
	uint32_t result = 0;
	
	for (ctr = 0; ctr < filterData->filterLen; ctr++)
	{
		/* Kein Ueberlauf möglich (255 * uint16_max < uint32_max) */
		result += filterData->filterContent[ctr];
	}
	
	result /= filterData->filterLen;
	
	if (UINT16_MAX < result)
	{
		result = UINT16_MAX;
	}
	
	return (uint16_t)result;
}

/* -----------------------------------------------------
 * --               Private functions                  --
 * ----------------------------------------------------- */
