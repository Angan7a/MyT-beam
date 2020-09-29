#pragma once

#include <Wire.h>
#include <Arduino.h>
#include "axp20x.h"
#include "config.h"
#include "Observer.h"




class I2C : public SubjectForObserv {

	AXP20X_Class axp;

	void readChStatus();

	static void setWasIRQ();

	static	bool pmu_irq;

	String baChStatus;
public:
	bool ssd1306_found = false;
	
	bool axp192_found = false;
	
	I2C();

	void scanDevices();

	void setAxp192();
	
	void wasIRQ();

};
