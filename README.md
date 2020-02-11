# SSD1306 - emWin - PSoC 6 SDK Configuration Files
This repository contains all of the emWin configuration files plus driver setup for the SSD1306 (driver chip) connected to a 128x64 OLED.  The SSD1306/OLED is the display that is attached to the CY8CKIT-032

This driver configures emWin to use FreeRTOS (e.g. for Delays)

To use this driver you need to
```
#include "SSD1306Driver.h"
```

To use this driver you should setup an I2C interface using the Cypress HAL, then call "SSD1306DriverInit" with a pointer to the I2C to use and the I2C address of the screen.  If you pass a 0 then it will default to the 0x32 (which seems to be the most common address.  The function prototype is:
```
void SSD1306DriverInit(cyhal_i2c_t *obj, uint8_t oledAddress);
```

E.G:

```
cyhal_i2c_t I2C;

/* Configuration to initialize the I2C block */
static cyhal_i2c_cfg_t i2c_config = {
	.is_slave = false,
	.frequencyhal_hz = 400000
};
cyhal_i2c_init(&I2C, CYBSP_I2C_SDA, CYBSP_I2C_SCL, NULL);
cyhal_i2c_configure(&I2C, &i2c_config);
SSD1306DriverInit(&I2C,0x32);
```

These files depend on emWin being part of your project.  You must add them either manually or by using the library manager.

# Adding this Driver to your project manually
You can add this driver plus emWin to your project by:
```
echo "https://github.com/cypresssemiconductorco/emwin/#release-v5.48.1" > emwin.lib
echo "https://github.com/iotexpert/p6sdk-ssd1306-emWin-config/#master" > p6sdk-ssd1306-emWin-config.lib
make getlibs
```
# Adding this Driver to your project with the Library Manager
If you are using the IoT Expert manifest this will show up in the library manager under the IoT Expert middleware.
![Exmaple Code Results](https://raw.githubusercontent.com/iotexpert/p6sdk-ssd1306-emWin-config/master/libraryManager.png)

## Example Code
This code will initailize the BSP, then display "Hello World" in the middle.
```
#include "cybsp.h"
#include "GUI.h"
#include "SSD1306Driver.h"

int main(void)
{
	/* Set up the device based on configurator selections */
	cybsp_init();

	cyhal_i2c_t I2C;

	/* Configuration to initialize the I2C block */
	static cyhal_i2c_cfg_t i2c_config = {
		.is_slave = false,
		.frequencyhal_hz = 400000
	};
	cyhal_i2c_init(&I2C, CYBSP_I2C_SDA, CYBSP_I2C_SCL, NULL);
	cyhal_i2c_configure(&I2C, &i2c_config);

	SSD1306DriverInit(&I2C,0x3C);

	GUI_Init();
	GUI_SetColor(GUI_WHITE);
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetFont(GUI_FONT_8_ASCII);
	GUI_SetTextAlign(GUI_TA_CENTER);
	GUI_DispStringAt("Hello World", GUI_GetScreenSizeX()/2,GUI_GetScreenSizeY()/2 - GUI_GetFontSizeY()/2);
}


```

![Exmaple Code Results](https://raw.githubusercontent.com/iotexpert/p6sdk-ssd1306-emWin-config/master/IMG_1350.jpg)
