#pragma once

#include "SSD1306.h"
#include "OLEDDisplayUi.h"
#include "Observer.h"

#define I2C_SDA             21
#define I2C_SCL             22

#define SSD1306_ADDRESS         0x3C
#define ENABLE_SSD1306


class Screen : public Observer {

	SSD1306 * oled;

	OLEDDisplayUi * ui;

	static void msOverlay(OLEDDisplay *display, OLEDDisplayUiState *state);

	static String batStatus;
	
public:
	Screen();

	void init() override;
	
	void loop() override;

	static void drawFrame2(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y);

	static void drawFrame3(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y);

	void updateDataFromSubject(const String & status) override;

};
