#include "GPS.h"
#include "Lora.h"
#include <string>

extern std::shared_ptr<ObserverAndSubject> lora;
extern std::shared_ptr<Observer> screen;


GPS::GPS() {
	gps = new TinyGPSPlus();
	packetGPS = new PacketGPS();
        Serial.printf("\nExten: \n");
	delay(100);
	Serial.println("All comms started888888888888888888888888888888888888888888");
	delay(100);
	SerialGPS.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
	delay(100);
	int i = 0;
	do {
		    if (myGPS.begin(SerialGPS)) {
			          Serial.println("Connected to GPS");
				        myGPS.setUART1Output(COM_TYPE_NMEA); //Set the UART port to output NMEA only
      myGPS.saveConfiguration(); //Save the current settings to flash and BBR
	    Serial.println("GPS serial connected, output set to NMEA");
	  myGPS.disableNMEAMessage(UBX_NMEA_GLL, COM_PORT_UART1);
	myGPS.disableNMEAMessage(UBX_NMEA_GSA, COM_PORT_UART1);
	      myGPS.disableNMEAMessage(UBX_NMEA_GSV, COM_PORT_UART1);
	    myGPS.disableNMEAMessage(UBX_NMEA_VTG, COM_PORT_UART1);
	  myGPS.disableNMEAMessage(UBX_NMEA_RMC, COM_PORT_UART1);
	myGPS.enableNMEAMessage(UBX_NMEA_GGA, COM_PORT_UART1);
		      myGPS.saveConfiguration(); //Save the current settings to flash and BBR
	    Serial.println("Enabled/disabled NMEA sentences");
	  break;
      }
        delay(1000);
	i++;
	  } while(i < 3);

addObserver(lora);
addObserver(screen);
}

void GPS::init() {}

void GPS::loop() {
static uint64_t gpsMap = 0;
int out = 0;
 while (SerialGPS.available())
            gps->encode(SerialGPS.read());

        if (millis() > 5000 && gps->charsProcessed() < 10) {
            snprintf(buff[0], sizeof(buff[0]), "T-Beam GPS");
            snprintf(buff[1], sizeof(buff[1]), "No GPS detected");
           // if (!ssd1306_found) {
                Serial.println(buff[1]);
           // }
            out = -1;
        }
        if (!gps->location.isValid()) {
            if (millis() - gpsMap > 1000) {
                snprintf(buff[0], sizeof(buff[0]), "T-Beam GPS");
                snprintf(buff[1], sizeof(buff[1]), "Positioning(%llu)", gpsSec++);
                //if (!ssd1306_found) {
                    Serial.println(buff[1]);
                //}
                gpsMap = millis();
            }
        } else {
            if (millis() - gpsMap > 1000) {
		    packetGPS->h = gps->time.hour();
		    packetGPS->m = gps->time.minute();
		    packetGPS->s = gps->time.second();
		    packetGPS->lng = gps->location.lng();
		    packetGPS->lat = gps->location.lat();
		    packetGPS->numSat = gps->satellites.value();

                snprintf(buff[0], sizeof(buff[0]), "UTC:%d:%d:%d", gps->time.hour(), gps->time.minute(), gps->time.second());
                snprintf(buff[1], sizeof(buff[1]), "LNG:%.4f", gps->location.lng());
                snprintf(buff[2], sizeof(buff[2]), "LAT:%.4f", gps->location.lat());
                snprintf(buff[3], sizeof(buff[3]), "satellites:%u", gps->satellites.value());
                //if (!ssd1306_found) {
                    Serial.println(buff[0]);
                    Serial.println(buff[1]);
                    Serial.println(buff[2]);
                    Serial.println(buff[3]);
               // }
                gpsMap = millis();
	out = gps->satellites.value();
		packetGPS->distFromTFO = gps->distanceBetween(packetGPS->lat, packetGPS->lng, 51.085010, 17.071220);
	notifyObserversGPS( * packetGPS);
            }
        }

}

void GPS::updateDataFromSubjectLora(const String & message, double rssi) {
	auto pos = message.indexOf("Lat:");
		double lat;
		double lng;

	if (pos != -1) {
		//double lat = (message.substring(pos, 8)).toDouble();
		lat = (message.substring(pos+4, 13)).toDouble();
		Serial.println("Recived pos GPS - lat: ");
		Serial.println(lat,4);
	}
	 pos = message.indexOf("Lng:");
	if (pos != -1) {
		//double lat = (message.substring(pos, 8)).toDouble();
		lng = (message.substring(pos+4, 26)).toDouble();
		Serial.println("Recived pos GPS - lng: ");
		Serial.println(lng, 4);
	}

	if (lat != 0 and lng != 0) {
		if (packetGPS->lng != 0) {
			packetGPS->distFromOtherDev = gps->distanceBetween(packetGPS->lat, packetGPS->lng, lat, lng);
		Serial.println(packetGPS->distFromOtherDev, 4);
		} else {
			packetGPS->distOtherFromTFO = gps->distanceBetween(lat, lng,51.085010, 17.071220);
		Serial.println(packetGPS->distOtherFromTFO, 4);
		}
			notifyObserversGPS( * packetGPS);
	}

}
