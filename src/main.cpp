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
#include "Lora.h"


std::shared_ptr<SubjectForObserv> i2c = std::make_shared<I2C> ();
std::shared_ptr<SubjectForObserv> button = std::make_shared<Button> (38);

std::shared_ptr<Observer> screen = std::make_shared<Screen> ();

std::shared_ptr<ObserverAndSubject> lora = std::make_shared<Lora> ();

void setup() {
	Serial.begin(115200);
	delay(1000);

	i2c->scanDevices();
	i2c->setAxp192();
	screen->init();
    lora->init();
    lora->addObserver(i2c->getGPS() );
}
void loop() {
//lora->send("Lat:13.2311512Lng:12.121222");
lora->received();
	i2c->wasIRQ();
	screen->loop();
	button->loop();
	delay(5000);
}

