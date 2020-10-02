#pragma once

#include "SSD1306.h"
#include "OLEDDisplayUi.h"
#include "Observer.h"
#include "PacketGPS.h"

#define I2C_SDA             21
#define I2C_SCL             22

#define SSD1306_ADDRESS         0x3C
#define ENABLE_SSD1306


class Screen : public Observer {

	SSD1306 * oled;

	OLEDDisplayUi * ui;

	static void msOverlay(OLEDDisplay *display, OLEDDisplayUiState *state);

	static String batStatus;

	static String GPS_line1;

	static String GPS_line2;

	static String GPS_line3;
	
public:
	Screen();

	void init() override;
	
	void loop() override;

	static void drawFrame2(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y);

	static void drawFrame3(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y);

	void updateDataFromSubjectBatCh(const String & status) override;

	void updateDataFromSubjectGPS(const PacketGPS & packetGPS) override;

	void updateDataFromSubjectButton() override; 

};
