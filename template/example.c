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

