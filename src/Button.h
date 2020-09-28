#pragma once
#include <Button2.h>
#include "config.h"
#include "Observer.h"

#define BUTTONS_MAP {BUTTON_PIN}

class Button : public Subject {

	static Button2 *pBtns;

	static constexpr uint8_t g_btns[] = BUTTONS_MAP;

public:

	static void button_callback(Button2 &b);

	void button_loop();

	void button_init();

};

