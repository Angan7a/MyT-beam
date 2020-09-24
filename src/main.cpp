/*
*   This factory is just to test LilyGo T-Beam series hardware
*   Created by Lewis he
* */

#include "Screen.h"
#include "axp20x.h"
#include "config.h"
#include "I2C.h"

I2C i2c{};
	Screen screen{};
bool ssd1306_found = false;
bool axp192_found = false;
//#define AXP192_SLAVE_ADDRESS    0x34


void setup() {
	Serial.begin(115200);
	delay(1000);

	i2c.scanDevices();
	i2c.setAxp192();
	screen.init();
}
void loop() {
	i2c.ss();
	screen.loop();	
	delay(90);
}

