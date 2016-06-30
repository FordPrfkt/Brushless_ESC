/*!
***     \file	  TWI_Handler.c
***     \ingroup  TWI_Handler
***     \author   Daniel
***     \date	  30.06.2016 19:28:05
***     \brief    TODO
***
******************************************************************************/

/* Header file guard symbol to prevent multiple includes */
#ifndef TWI_Handler_H_
#define TWI_Handler_H_

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
#define TWI_NUM_CMDS 8

typedef enum TWI_Cmd_e
{
    TWI_CMD_TO_FBL = 0xA0,
    TWI_CMD_CONFIG = 0x10,
    TWI_CMD_SAVE_CONFIG = 0x12,
    TWI_CMD_ARM = 0x20,
    TWI_CMD_THROTTLE = 0x30,
    TWI_CMD_PPM = 0x40,
    TWI_CMD_STATUS = 050,
    TWI_CMD_ERRORS = 0x51
}TWI_Cmd_t;

typedef struct TWI_Cmd_Data_s
{
    TWI_Cmd_t cmd;
    uint8_t paramLen;
    uint8_t resultLen;
}TWI_Cmd_Data_t;

/*=============================================================================
=======                              EXPORTS                            =======
=============================================================================*/

/* end of storage class specifier if used with C++ */
#ifdef  __cplusplus
}
#endif

#endif /*TWI_Handler_H_*/
