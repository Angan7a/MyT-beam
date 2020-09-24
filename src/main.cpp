/*
*   This factory is just to test LilyGo T-Beam series hardware
*   Created by Lewis he
* */

#include "Screen.h"
#include "axp20x.h"
#define PMU_IRQ             35
AXP20X_Class axp;
bool pmu_irq = false;
String baChStatus = "No charging";

	Screen screen{};
bool ssd1306_found = false;
bool axp192_found = false;
//#define AXP192_SLAVE_ADDRESS    0x34


void setup() {
	Serial.begin(115200);
	delay(1000);
	Wire.begin(I2C_SDA, I2C_SCL);

	screen.init();
}
void loop() {
	screen.loop();	
	delay(90);
}

