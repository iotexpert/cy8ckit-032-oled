/******************************************************************************
* File Name: i2c_portapi.c
*
* Description: This file contains the I2C port API functions that will be
*               used by emWin to communicate with the OLED display
*
* Hardware Dependency: CY8CKIT-032 AFE Shield
*
*******************************************************************************
* Copyright (2019), Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* (“Software”), is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries (“Cypress”) and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software (“EULA”).
*
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypress’s integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress 
* reserves the right to make changes to the Software without notice. Cypress 
* does not assume any liability arising out of the application or use of the 
* Software or any product or circuit described in the Software. Cypress does 
* not authorize its products for use in any products where a malfunction or 
* failure of the Cypress product may reasonably be expected to result in 
* significant property damage, injury or death (“High Risk Product”). By 
* including Cypress’s product in a High Risk Product, the manufacturer of such 
* system or application assumes all risk of such use and in doing so agrees to 
* indemnify Cypress against all liability.
*******************************************************************************/

#include "GUI.h"
#include "i2c_portapi.h"
#include "cyhal.h"
#include "cybsp.h"
#include "stdlib.h"

/*********************************************************************
*
*       Defines: Configuration
*
**********************************************************************
  Needs to be adapted to custom hardware.
*/
/* I2C port to communicate with the OLED display controller */
cyhal_i2c_t I2C;

/* I2C slave address, Command and Data byte prefixes for the display controller */
#define OLED_CONTROL_BYTE_CMD       (0x00)
#define OLED_CONTROL_BYTE_DATA      (0x40)

#ifndef OLED_I2C_ADDRESS
#define OLED_I2C_ADDRESS            (0x3C)
#endif

#ifndef OLED_I2C_SDA
#define OLED_I2C_SDA				   	(CYBSP_I2C_SDA)
#endif

#ifndef OLED_I2C_SCL
#define OLED_I2C_SCL					(CYBSP_I2C_SCL)
#endif

#ifndef OLED_I2C_SPEED
/* I2C bus speed */
#define OLED_I2C_SPEED                   (400000)
#endif

/* Configuration to initialize the I2C block */
static cyhal_i2c_cfg_t i2c_config = {
	.is_slave = false,
	.address = OLED_I2C_ADDRESS,
	.frequencyhal_hz = OLED_I2C_SPEED
};

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/*******************************************************************************
* Function Name: void I2C_Init(void)
********************************************************************************
*
* Summary: This function initializes I2C interface.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void I2C_Init(void) 
{
    cyhal_i2c_init(&I2C, OLED_I2C_SDA, OLED_I2C_SCL, NULL);
    cyhal_i2c_configure(&I2C, &i2c_config);
}

/*******************************************************************************
* Function Name: void I2C_WriteCommandByte(unsigned char c) 
********************************************************************************
*
* Summary: This function writes a command byte to the display controller with A0 = 0
*
* Parameters:
*  unsigned char c - command to be written to the display controller
*
* Return:
*  None
*
*******************************************************************************/
void I2C_WriteCommandByte(unsigned char c) 
{
    uint8_t buff[2];
    
    /* The first byte of the buffer tells the display that the following byte
        is a command */
    buff[0] = OLED_CONTROL_BYTE_CMD;
    buff[1] = (char)c;
    
    /* Write the buffer to display controller */
    cyhal_i2c_master_write(&I2C, OLED_I2C_ADDRESS, buff, 2, 0, true);
}

/*******************************************************************************
* Function Name: void I2C_WriteDataByte(unsigned char c) 
********************************************************************************
*
* Summary: This function writes a data byte to the display controller with A0 = 1
*
* Parameters:
*  unsigned char c - data to be written to the display controller
*
* Return:
*  None
*
*******************************************************************************/
void I2C_WriteDataByte(unsigned char c) 
{
	uint8_t buff[2];
    
    /* First byte of the buffer tells the display controller that the following byte 
        is a data byte */
    buff[0] = OLED_CONTROL_BYTE_DATA;
    buff[1] = c;

    /* Write the buffer to display controller */
    cyhal_i2c_master_write(&I2C, OLED_I2C_ADDRESS, buff, 2, 0, true);
}

/*******************************************************************************
* Function Name: void I2C_WriteDataStream(unsigned char * pData, int NumBytes) 
********************************************************************************
*
* Summary: This function writes multiple data bytes to the display controller with A0 = 1
*
* Parameters:
*  unsigned char *pData - Pointer to the buffer that has data
*  int numBytes - Number of bytes to be written to the display controller
*
* Return:
*  None
*
*******************************************************************************/
void I2C_WriteDataStream(unsigned char * pData, int numBytes) 
{   
	uint8_t* buff = (uint8_t*)malloc(numBytes+1);
    
    /* Tell the display controller that the following bytes are data bytes */
    buff[0] = OLED_CONTROL_BYTE_DATA;

    /* Copy data bytes to buffer array */
    memcpy(&buff[1], pData, numBytes);

    /* Write all the data bytes to the display controller */
    cyhal_i2c_master_write(&I2C, OLED_I2C_ADDRESS, buff, numBytes+1, 0, true);
    free(buff);
}

/*******************************************************************************
* Function Name: void I2C_ReadDataStream(unsigned char * pData, int numBytes)  
********************************************************************************
*
* Summary: This function reads multiple data bytes from the display controller with A0 = 1
*
* Parameters:
*  unsigned char *pData - Pointer to the destination buffer
*  int numBytes - Number of bytes to be read from the display controller
*
* Return:
*  None
*
*******************************************************************************/
void I2C_ReadDataStream(unsigned char * pData, int numBytes) 
{
    /* SSD1306 is not readable through i2c. Using cache instead (LCDConf.c, GUIDRV_SPAGE_1C1)*/
}

/*************************** End of file ****************************/
