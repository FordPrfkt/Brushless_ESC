/*!
***     \file	  I2C.c
***     \ingroup  I2C
***     \author   Daniel
***     \date	  07.11.2015 16:44:46
***     \brief    TODO
***
******************************************************************************/

/* Header file guard symbol to prevent multiple includes */
#ifndef I2C_H_
#define I2C_H_

/* storage class specifier if used with C++ */
#ifdef  __cplusplus
  extern "C" {
#endif

/*=============================================================================
=======                            INCLUDES                             =======
=============================================================================*/
#include <stdbool.h>
/*=============================================================================
=======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
=============================================================================*/
#define I2C_NUM_CMDS 12

typedef enum I2C_Cmd_e
{
    I2C_CMD_TO_FBL = 0xA0,
    I2C_CMD_SET_CONFIG = 0x20,
    I2C_CMD_GET_CONFIG = 0x21,
    I2C_CMD_SAVE_CONFIG = 0x22,
    I2C_CMD_ARM = 0x30,
    I2C_CMD_SET_THROTTLE = 0x31,
    I2C_CMD_GET_THROTTLE = 0x32,
    I2C_CMD_GET_PPM = 0x33,
    I2C_CMD_GET_STATUS = 0x40,
    I2C_CMD_GET_ERRORS = 0x41
}I2C_Cmd_t;

typedef struct I2C_Cmd_Data_s
{
    I2C_Cmd_t cmd;
    uint8_t paramLen;
    uint8_t resultLen;
}I2C_Cmd_Data_t;

/*=============================================================================
=======                       CONSTANTS  &  TYPES                       =======
=============================================================================*/

/*=============================================================================
=======                              EXPORTS                            =======
=============================================================================*/
void I2C_SlaveInit(void);
void I2C_SetTransmitBuffer(uint8_t bufLen, void *data);
bool I2C_Cmd_Callback(uint8_t cmd, volatile void *param, uint8_t paramLen);

/* end of storage class specifier if used with C++ */
#ifdef  __cplusplus
}
#endif

#endif /*I2C_H_*/
