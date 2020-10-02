#include "I2C.h"
#include "Screen.h"
 
extern std::shared_ptr<Observer> screen;

I2C::I2C() {
	Wire.begin(I2C_SDA, I2C_SCL);
}


void I2C::scanDevices() {
	byte err, addr;
	int nDevices = 0;
	for (addr = 1; addr < 127; addr++) {
        	Wire.beginTransmission(addr);
	        err = Wire.endTransmission();
        	if (err == 0) {
            		Serial.print("I2C device found at address 0x");
            		if (addr < 16)
                		Serial.print("0");
            		Serial.print(addr, HEX);
            		Serial.println(" !");
            		nDevices++;

			if (addr == SSD1306_ADDRESS) {
				ssd1306_found = true;
				Serial.println("ssd1306 display found");
			}
		        if (addr == AXP192_SLAVE_ADDRESS) {
			        axp192_found = true;
			        Serial.println("axp1ds2 PMU found");
			}
		} else if (err == 4) {
		        Serial.print("Unknow error at address 0x");
		        if (addr < 16)
		            Serial.print("0");
		        Serial.println(addr, HEX);
		}
    	}
	
	if (axp192_found) {
		readChStatus();
		addObserver(screen);
	}

        if (nDevices == 0)
            Serial.println("No I2C devices found\n");
        else
            Serial.println("done\n");
}

void I2C::wasIRQ() {
    if (axp192_found && pmu_irq) {
	readChStatus();
    }
     gpsP->loop();
}

void I2C::readChStatus() {
        pmu_irq = false;
	axp.readIRQ();
        if (axp.isChargingIRQ()) {
            baChStatus = "Charging";
        } else {
            baChStatus = "No Charging";
        }
        if (axp.isVbusRemoveIRQ()) {
            baChStatus = "No Charging";
        }
	notifyObserversBatCh(baChStatus);
        digitalWrite(2, !digitalRead(2));
        axp.clearIRQ();
}

bool I2C::pmu_irq = false;

void I2C::setWasIRQ() {
	pmu_irq = true;
}

void I2C::setAxp192() {
    if (axp192_found) {
        if (!axp.begin(Wire, AXP192_SLAVE_ADDRESS)) {
            Serial.println("AXP192 Begin PASS");
        } else {
            Serial.println("AXP192 Begin FAIL");
        }

        // axp.setChgLEDMode(LED_BLINK_4HZ);

        Serial.printf("DCDC1: %s\n", axp.isDCDC1Enable() ? "ENABLE" : "DISABLE");
        Serial.printf("DCDC2: %s\n", axp.isDCDC2Enable() ? "ENABLE" : "DISABLE");
        Serial.printf("LDO2: %s\n", axp.isLDO2Enable() ? "ENABLE" : "DISABLE");
        Serial.printf("LDO3: %s\n", axp.isLDO3Enable() ? "ENABLE" : "DISABLE");
        Serial.printf("DCDC3: %s\n", axp.isDCDC3Enable() ? "ENABLE" : "DISABLE");
        Serial.printf("Exten: %s\n", axp.isExtenEnable() ? "ENABLE" : "DISABLE");

        Serial.println("----------------------------------------");

axp.setPowerOutPut(AXP192_LDO3, AXP202_ON); // GPS main power
        axp.setPowerOutPut(AXP192_LDO2, AXP202_ON);
        axp.setPowerOutPut(AXP192_LDO3, AXP202_ON);
        axp.setPowerOutPut(AXP192_DCDC2, AXP202_ON);
        axp.setPowerOutPut(AXP192_EXTEN, AXP202_ON);
        axp.setPowerOutPut(AXP192_DCDC1, AXP202_ON);
axp.setPowerOutPut(AXP192_DCDC3, AXP202_ON);
        axp.setDCDC1Voltage(3300);  //esp32 core VDD    3v3
        axp.setLDO2Voltage(3300);   //LORA VDD set 3v3
        axp.setLDO3Voltage(3300);   //GPS VDD      3v3

        Serial.printf("DCDC1: %s\n", axp.isDCDC1Enable() ? "ENABLE" : "DISABLE");
        Serial.printf("DCDC2: %s\n", axp.isDCDC2Enable() ? "ENABLE" : "DISABLE");
        Serial.printf("LDO2: %s\n", axp.isLDO2Enable() ? "ENABLE" : "DISABLE");
        Serial.printf("LDO3: %s\n", axp.isLDO3Enable() ? "ENABLE" : "DISABLE");
        Serial.printf("DCDC3: %s\n", axp.isDCDC3Enable() ? "ENABLE" : "DISABLE");
        Serial.printf("Exten: %s\n", axp.isExtenEnable() ? "ENABLE" : "DISABLE");


        pinMode(PMU_IRQ, INPUT_PULLUP);
	attachInterrupt(PMU_IRQ, setWasIRQ , FALLING);

        axp.adc1Enable(AXP202_BATT_CUR_ADC1, 1);
        axp.enableIRQ(AXP202_VBUS_REMOVED_IRQ | AXP202_VBUS_CONNECT_IRQ | AXP202_BATT_REMOVED_IRQ | AXP202_BATT_CONNECT_IRQ, 1);
        axp.clearIRQ();

	readChStatus();

    } else {
        Serial.println("AXP192 not found");
    }
	gpsP = std::make_shared<GPS> ();
	gpsP->addObserver(screen);
}


