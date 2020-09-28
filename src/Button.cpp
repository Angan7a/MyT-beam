#include "Button.h"

extern std::shared_ptr<Observer> screen;

void Button::button_callback(Button2 &b) {
	for (int i = 0; i < ARRARY_SIZE(g_btns); ++i) {
		if (pBtns[i] == b) {
		//	notifyObservers();	
		}
	}
}

void Button::button_loop()
{
	for (int i = 0; i < ARRARY_SIZE(g_btns); ++i) {
	          pBtns[i].loop();
        }
}

Button2 * Button::pBtns;

void Button::button_init() {
	uint8_t args = ARRARY_SIZE(g_btns);
	pBtns = new Button2 [args];
	for (int i = 0; i < args; ++i) {
		pBtns[i] = Button2(g_btns[i]);
		pBtns[i].setPressedHandler(button_callback);
	}
	addObserver(screen);
}
