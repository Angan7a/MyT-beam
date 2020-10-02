#include "Screen.h"
#define ARRARY_SIZE(a)   (sizeof(a) / sizeof(a[0]))

Screen::Screen() {
	oled = new SSD1306 {SSD1306_ADDRESS, I2C_SDA, I2C_SCL};
	ui = new OLEDDisplayUi {oled}; 
}

void Screen::init()
{
#ifdef ENABLE_SSD1306
   // if (!ssd1306_found) {
   //     Serial.println("SSD1306 not found");
   //     return;
  //  }
    if (oled->init()) {
        oled->flipScreenVertically();
        oled->setFont(ArialMT_Plain_16);
        oled->setTextAlignment(TEXT_ALIGN_CENTER);
    } else {
        Serial.println("SSD1306 Begin FAIL");
    }
    Serial.println("SSD1306 Begin PASS");
    ui->setTargetFPS(30);
    ui->disableAutoTransition();
    ui->setIndicatorPosition(BOTTOM);
    ui->setIndicatorDirection(LEFT_RIGHT);
    ui->setFrameAnimation(SLIDE_LEFT);
//    ui->setFrames(frames, ARRARY_SIZE(frames));
//    if (axp192_found) {
	static    OverlayCallback overlays[] = { msOverlay };
	static    FrameCallback frames[] = { drawFrame2, drawFrame3};
        ui->setFrames(frames, ARRARY_SIZE(frames));
        ui->setOverlays(overlays, ARRARY_SIZE(overlays));
  //  }
#endif
}

String Screen::batStatus = "None";

void Screen::msOverlay(OLEDDisplay *display, OLEDDisplayUiState *state)
{
    static char volbuffer[128];
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->setFont(ArialMT_Plain_10);

    display->drawString(0, 0, batStatus);

   // if (axp.isBatteryConnect()) {
   //     snprintf(volbuffer, sizeof(volbuffer), "%.2fV/%.2fmA", axp.getBattVoltage() / 1000.0, axp.isChargeing() ? axp.getBattChargeCurrent() : axp.getBattDischargeCurrent());
   //     display->drawString(62, 0, volbuffer);
//    } else {
        multi_heap_info_t info;
        heap_caps_get_info(&info, MALLOC_CAP_INTERNAL);
        snprintf(volbuffer, sizeof(volbuffer), "%u/%uKB",  info.total_allocated_bytes / 1024, info.total_free_bytes / 1024);
        display->drawString(75, 0, volbuffer);
  //  }
}

String Screen::GPS_line1 = "e";
String Screen::GPS_line2 = "e";
String Screen::GPS_line3 = "e";

void Screen::drawFrame2(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    display->setFont(ArialMT_Plain_10);
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->drawString(64 + x, 11 + y, GPS_line1);
    display->drawString(64 + x, 22 + y, GPS_line2);
    display->drawString(64 + x, 33 + y, GPS_line3);
}

void Screen::drawFrame3(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    display->setFont(ArialMT_Plain_10);
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->drawString(64 + x, 9 + y, "buff[0]");
    display->drawString(64 + x, 22 + y,  "No message");
    display->drawString(64 + x, 35 + y, "buff[1]");
}

void Screen::loop()
{
	  ui->update();
}

void Screen::updateDataFromSubjectGPS(const PacketGPS & packetGPS) {
		GPS_line1 = "Num Sat: " + String(packetGPS.numSat);
		GPS_line2 = packetGPS.numSat ? ("Lng: " + String(packetGPS.lng) + ", Lat: " + String(packetGPS.lat)) : "";
		GPS_line3 = packetGPS.numSat ? (String(packetGPS.h + 2) + ":" + String(packetGPS.m) + ":" + String(packetGPS.s) + ":") : "";
}

void Screen::updateDataFromSubjectBatCh(const String & status) {
		batStatus = status;
}

void Screen::updateDataFromSubjectButton() {
		ui->nextFrame();
}

