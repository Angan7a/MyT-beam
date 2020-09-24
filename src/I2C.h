#pragma once

#include <Wire.h>
#include <Arduino.h>
#include "axp20x.h"
#include "config.h"




class I2C {

	AXP20X_Class axp;


public:
	bool ssd1306_found = false;
	
	bool axp192_found = false;

static	bool pmu_irq;

	String baChStatus;
	
	I2C();

	void scanDevices();

	void setAxp192();
	
	void ss();

	static void s();
};
