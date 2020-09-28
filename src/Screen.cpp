#include "Screen.h"
#include "config.h"

Screen::Screen() {
	oled = new SSD1306(SSD1306_ADDRESS, I2C_SDA, I2C_SCL);
	ui = new OLEDDisplayUi(oled); 
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

void Screen::drawFrame2(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    display->setFont(ArialMT_Plain_10);
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->drawString(64 + x, 11 + y, "buff[0]");
    display->drawString(64 + x, 22 + y, "buff[1]");
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

void Screen::updateDataFromBaCh(const String & status) {
		batStatus = status;
}

void Screen::nextFrame() {
	ui->nextFrame();
}

