#include "Button.h"
#include "Screen.h"

extern std::shared_ptr<Observer> screen;

Button::Button(int pin) {
	userButton =  std::make_shared<OneButton> (pin, true, true);
	userButton->attachClick(userButtonPressed);

	addObserver(screen);
}

void Button::userButtonPressed() {
//	notifyObserversButton();
}

void Button::loop() {
	userButton->tick();
}
