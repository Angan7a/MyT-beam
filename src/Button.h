#pragma once

#include <memory>
#include "Observer.h"
#include <OneButton.h>


class Button : public SubjectButton {
	std::shared_ptr<OneButton> userButton; 

	static void userButtonPressed();
public:
	Button(int pin);
	
	void loop();
};
