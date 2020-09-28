/*
*   This factory is just to test LilyGo T-Beam series hardware
*   Created by Lewis he
* */

#include "Screen.h"
#include "axp20x.h"
#include "config.h"
#include "I2C.h"
//#include "Button.h"
#include <OneButton.h>


OneButton userButton =  OneButton(38, true, true);


I2C i2c{};

std::shared_ptr<Observer> screen = std::make_shared<Screen> ();
//std::shared_ptr<Subject> button = std::make_shared<Button> ();

bool ssd1306_found = false;
bool axp192_found = false;
//#define AXP192_SLAVE_ADDRESS    0x34

void userButtonPressed()
{
	screen->nextFrame();
}

void setup() {
	Serial.begin(115200);
	delay(1000);

	i2c.scanDevices();
	i2c.setAxp192();
	screen->init();
	        userButton.attachClick(userButtonPressed);
//	button->init();
}
void loop() {
	i2c.wasIRQ();
	screen->loop();	
//	button->button_loop();
userButton.tick();
	delay(9);
}

