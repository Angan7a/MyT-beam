#include "GPS.h"

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
            }
        }
	notifyObserversGPS( * packetGPS);

}

