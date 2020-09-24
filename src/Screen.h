#pragma once

#include "SSD1306.h"
#include "OLEDDisplayUi.h"
#define I2C_SDA             21
#define I2C_SCL             22

#define SSD1306_ADDRESS         0x3C
#define ENABLE_SSD1306


class Screen {

	SSD1306 *oled;

	OLEDDisplayUi *ui;

	static void msOverlay(OLEDDisplay *display, OLEDDisplayUiState *state);
public:

	static String batStatus;

	Screen();

	void init();
	
	void loop();

	static void drawFrame2(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y);

	static void drawFrame3(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y);
};
