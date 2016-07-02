/*!
***     \file	  SoundData.c
***     \ingroup  SoundData
***     \author   Daniel
***     \date	  22.03.2016 00:39:34
***     \brief    TODO
***
******************************************************************************/

/* Header file guard symbol to prevent multiple includes */
#ifndef SoundData_H_
#define SoundData_H_

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
typedef struct SND_SoundNote_s
{
    const uint16_t freq;
	const uint16_t duration;
}SND_SoundNote_t;

typedef enum SND_SoundList_e
{
	SND_START_SOUND = 0,
	SND_CAL_BEGIN,
	SND_CAL_END,
	SND_CAL_ABORT,
	SND_ARM,
	SND_DISARM,
	SND_ERROR,
	SND_BEEP,
	SND_NUM_SOUNDS
}SND_SoundList_t;

/*=============================================================================
=======                              EXPORTS                            =======
=============================================================================*/
uint8_t SND_GetSoundLength(SND_SoundList_t soundId);
SND_SoundNote_t* SND_GetNote(SND_SoundList_t soundId, uint8_t note);

/* end of storage class specifier if used with C++ */
#ifdef  __cplusplus
}
#endif

#endif /*SoundData_H_*/
