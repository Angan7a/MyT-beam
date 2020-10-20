#pragma once
#include <RadioLib.h>
#include <memory>
#include "board_def.h"
#include "Arduino.h"

class Lora : public SX1276 {
public:
	static Lora * instance;

	static volatile bool enableInterrupt;

	static volatile bool receivedFlag;

	bool loraBeginOK; 

	char buff[5][256];

	String recv = "";

	Lora();

	static void setFlag(void);

	void send();

	void received();
	
	void init();
};
