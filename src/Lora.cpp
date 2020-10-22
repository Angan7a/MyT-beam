#include "Lora.h"
#include "Screen.h"

Lora * Lora::instance;

extern std::shared_ptr<Observer> screen;

//extern std::shared_ptr<Observer> lora;

Lora::Lora() : SX1276(new Module(LORA_SS, LORA_DI0, LORA_RST, LORA_BUSY)) {

	instance = this;

	addObserver(screen);

}

	 volatile bool Lora::enableInterrupt = true;

	 volatile bool Lora::receivedFlag = false;

void Lora::setFlag(void)
	
{
    // check if the interrupt is enabled
    if (!enableInterrupt) {
        return;
    }
    // we got a packet, set the flag
    receivedFlag = true;
}



void Lora::init() {
//	 pointerToClass = this;
    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
    Serial.print(F("[Radio] Initializing ... "));
    int state = SX1276::begin(BAND);
    if (state == ERR_NONE) {
        loraBeginOK = true;
        Serial.println(F("success!"));
    } else {
        Serial.print(F("failed, code "));
        Serial.println(state);
        while (true);
    }

    // set the function that will be called
    // when new packet is received
                Serial.print(F("[RADIO] Starting to listen ... sadasdasdasdadada"));

                state = SX1276::startReceive();
                if (state == ERR_NONE) {
                    Serial.println(F("success!"));
                } else {
                    Serial.print(F("failed, code "));
                    Serial.println(state);
                    while (true);
                }
		SX1276::setDio0Action(setFlag);
}


void Lora::send(const String & message) {
        snprintf(buff[0], sizeof(buff[0]), "T-Beam Lora Sender");
        if (!loraBeginOK) {
            snprintf(buff[1], sizeof(buff[1]), "Lora Begin FAIL");
        //    if (!ssd1306_found) {
                Serial.println(buff[1]);
          //  }
            return;
        }
        //static uint32_t loraMap = 0;
  //      static double loraMap = 20.1234;

  //      if (millis() - loraMap > 3000) {
            int transmissionState = ERR_NONE;
            transmissionState = startTransmit(message.c_str());
            // check if the previous transmission finished
            if (receivedFlag) {
                // disable the interrupt service routine while
                // processing the data
                enableInterrupt = false;
                // reset flag
                receivedFlag = false;
                if (transmissionState == ERR_NONE) {
                    // packet was successfully sent
                    Serial.println(F("transmission finished!"));
                    // NOTE: when using interrupt-driven transmit method,
                    //       it is not possible to automatically measure
                    //       transmission data rate using getDataRate()

                } else {
                    Serial.print(F("failed, code "));
                    Serial.println(transmissionState);
                }
                // wait a second before transmitting again
                // delay(1000);

                // send another one
//                Serial.print(F("[RADIO] Sending another packet ... "));

                // you can transmit C-string or Arduino string up to
                // 256 characters long
//                transmissionState = startTransmit(String(loraMap, 2).c_str());

                // you can also transmit byte array up to 256 bytes long
                /*
                  byte byteArr[] = {0x01, 0x23, 0x45, 0x67,
                                    0x89, 0xAB, 0xCD, 0xEF};
                  int state = radio->startTransmit(byteArr, 8);
                */

                // we're ready to send more packets,
                // enable interrupt service routine
                enableInterrupt = true;
  //          }
   //         snprintf(buff[1], sizeof(buff[1]), "Send %f", loraMap);
   //         loraMap += 4.3 ; //millis();
            //if (!ssd1306_found) {
       //         Serial.println(buff[1]);
     //      // }
        }

}

void Lora::received() {
	SX1276::startReceive();
                //Serial.println("buff[1]");
        if (!loraBeginOK) {
            recv =  "Lora Begin FAIL";
        //    if (!ssd1306_found) {
                Serial.println(recv);
          ///  }
            return;
        }
        snprintf(buff[0], sizeof(buff[0]), "T-Beam Lora Received");

        // check if the flag is set
        if (instance->receivedFlag) {
            // disable the interrupt service routine while
            // processing the data
            enableInterrupt = false;

            // reset flag
            instance->receivedFlag = false;

            // you can read received data as an Arduino String
            int state = SX1276::readData(recv);

            // you can also read received data as byte array
            /*
              byte byteArr[8];
              int state = radio->readData(byteArr, 8);
            */

            if (state == ERR_NONE) {
                // packet was successfully received
                Serial.println(F("[RADIO] Received packet!"));

                // print data of the packet
                Serial.print(F("[RADIO] Data:\t\t"));
                Serial.println(recv);

                // print RSSI (Received Signal Strength Indicator)
                Serial.print(F("[RADIO] RSSI:\t\t"));
                Serial.print(getRSSI());
                Serial.println(F(" dBm"));
		double r = getRSSI();
                snprintf(buff[1], sizeof(buff[1]), "rssi:%.2f dBm", r);
		notifyObserversLora(recv, r);

                // print SNR (Signal-to-Noise Ratio)
                Serial.print(F("[RADIO] SNR:\t\t"));
                Serial.print(getSNR());
                Serial.println(F(" dB"));

            } else if (state == ERR_CRC_MISMATCH) {
                // packet was received, but is malformed
                Serial.println(F("CRC error!"));

            } else {
               // some other error occurred
                Serial.print(F("failed, code "));
                Serial.println(state);

            }

            // put module back to listen mode
	    SX1276::startReceive();

            // we're ready to receive more packets,
            // enable interrupt service routine
            enableInterrupt = true;
        }

	
}

void Lora::updateDataFromSubjectGPS(const PacketGPS & packetGPS) {
	String gps_data = "Lat:" + String(packetGPS.getLat(),6) + "Lng:" + String(packetGPS.getLng(),6);
	send(gps_data);
}
