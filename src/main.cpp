/*
*   This factory is just to test LilyGo T-Beam series hardware
*   Created by Lewis he
* */

#include "Screen.h"
#include "axp20x.h"
#define PMU_IRQ             35
AXP20X_Class axp;
bool pmu_irq = false;
String baChStatus = "No charging";

	Screen screen{};
bool ssd1306_found = false;
bool axp192_found = false;
//#define AXP192_SLAVE_ADDRESS    0x34

void scanI2Cdevice(void)
{
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
																					                Serial.println("axp192 PMU found");
																							            }
																		        } else if (err == 4) {
																				            Serial.print("Unknow error at address 0x");
																					                if (addr < 16)
																								                Serial.print("0");
																							            Serial.println(addr, HEX);
																								            }
						        }
		        if (nDevices == 0)
				        Serial.println("No I2C devices found\n");
			    else
				            Serial.println("done\n");
}

void setup() {
	Serial.begin(115200);
	delay(1000);
	Wire.begin(I2C_SDA, I2C_SCL);

scanI2Cdevice();
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

        axp.setPowerOutPut(AXP192_LDO2, AXP202_ON);
        axp.setPowerOutPut(AXP192_LDO3, AXP202_ON);
        axp.setPowerOutPut(AXP192_DCDC2, AXP202_ON);
        axp.setPowerOutPut(AXP192_EXTEN, AXP202_ON);
        axp.setPowerOutPut(AXP192_DCDC1, AXP202_ON);
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
        attachInterrupt(PMU_IRQ, [] {
            pmu_irq = true;
        }, FALLING);

        axp.adc1Enable(AXP202_BATT_CUR_ADC1, 1);
        axp.enableIRQ(AXP202_VBUS_REMOVED_IRQ | AXP202_VBUS_CONNECT_IRQ | AXP202_BATT_REMOVED_IRQ | AXP202_BATT_CONNECT_IRQ, 1);
        axp.clearIRQ();

        if (axp.isChargeing()) {
            baChStatus = "Charging";
        }
    } else {
        Serial.println("AXP192 not found");
    }

	screen.init();
}
void loop() {
	screen.loop();	
	delay(90);
}

