#ifndef SSD1306_DRIVER_H
#define SSD1306_DRIVER_H
#include "cyhal.h"


void SSD1306DriverInit(cyhal_i2c_t *obj,uint8_t oledAddress);


void          SSD1306_WriteCommandByte(unsigned char c);
void          SSD1306_WriteDataByte(unsigned char c);
void          SSD1306_WriteDataStream(unsigned char * pData, int NumBytes);
void          SSD1306_ReadDataStream(unsigned char * pData, int NumBytes);

#endif
