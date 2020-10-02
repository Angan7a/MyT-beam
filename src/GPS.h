#pragma once

#include "config.h"
#include <Wire.h>
#include <SparkFun_Ublox_Arduino_Library.h>
#include "Observer.h"
#include <Arduino.h>
#include <TinyGPS++.h>

class GPS : public SubjectGPS {
	SFE_UBLOX_GPS myGPS;

	HardwareSerial SerialGPS{1};

	TinyGPSPlus * gps;

	char buff[5][256];
	
	uint64_t gpsSec = 0;

public:
	GPS();

	void init();

	void loop();
};

