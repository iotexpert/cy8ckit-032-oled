# SSD1306 - emWin - PSoC 6 SDK Configuration Files
This repository contains all of the emWin configuration files plus driver setup for the SSD1306 (driver chip) connected to the 128x64 OLED.  The SSD1306/OLED is the display that is attached to the CY8CKIT-032

These configuration files use the PSoC 6 SDK HAL to setup an I2C and write to the display.

These files depend on emWin being part of your project.  You must add them either manually or by using the library manager.

# Adding to your project manually
You can add this to your project by
```
echo "https://github.com/iotexpert/p6sdk-ssd1306-emWin-config/#master" > p6sdk-ssd1306-emWin-config.lib
make getlibs
```
# Adding to your project with Library Manager
If you are using the IoT Expert manifest this will show up in the library manager under the IoT Expert middleware.
![Exmaple Code Results](https://raw.githubusercontent.com/iotexpert/p6sdk-ssd1306-emWin-config/master/libraryManager.png)

## Example Code
This code will initailize the BSP, then display "Hello World" in the middle.
https://raw.githubusercontent.com/iotexpert/p6sdk-ssd1306-emWin-config/master/libraryManager.png
```
#include "cybsp.h"
#include "GUI.h"

int main(void)
{
    /* Set up the device based on configurator selections */
    cybsp_init();

    GUI_Init();
    GUI_SetColor(GUI_WHITE);
    GUI_SetBkColor(GUI_BLACK);
    GUI_SetFont(GUI_FONT_8_ASCII);
    GUI_SetTextAlign(GUI_TA_CENTER);
    GUI_DispStringAt("Hello World", GUI_GetScreenSizeX()/2,GUI_GetScreenSizeY()/2 - GUI_GetFontSizeY()/2);
}

```

![Exmaple Code Results](https://raw.githubusercontent.com/iotexpert/p6sdk-ssd1306-emWin-config/master/IMG_1350.jpg)
