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
