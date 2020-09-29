#include "Button.h"

Button::Button(int pin) {
	userButton =  std::make_shared<OneButton> (pin, true, true);
	userButton->attachClick(userButtonPressed);

}

void Button::userButtonPressed() {
	notifyObservers();
}

void Button::loop() {
	userButton->tick();
}
