/*
*   This factory is just to test LilyGo T-Beam series hardware
*   Created by Lewis he
* */

#include "Screen.h"
#include "axp20x.h"
#include "config.h"
#include "I2C.h"
#include "Button.h"
#include "GPS.h"

//OneButton userButton =  OneButton(38, true, true);

std::shared_ptr<SubjectForObserv> i2c = std::make_shared<I2C> ();
std::shared_ptr<SubjectForObserv> button = std::make_shared<Button> (38);

std::shared_ptr<Observer> screen = std::make_shared<Screen> ();


bool ssd1306_found = false;
bool axp192_found = false;
//#define AXP192_SLAVE_ADDRESS    0x34


void userButtonPressed()
{
	//	screen->nextFrame();
}


void setup() {
	Serial.begin(9600);
	delay(1000);

	i2c->scanDevices();
	i2c->setAxp192();
	screen->init();
button->addObserver(screen);
}
void loop() {
	Serial.println(" w main");
	i2c->wasIRQ();
	screen->loop();
	button->loop();
	delay(50);
}

