#pragma once

#include <vector>
#include <memory>
#include <WString.h>

class Observer {

public:
	virtual void updateDataFromBaCh(const String & status) = 0;
	virtual void init() = 0;
	virtual void loop() = 0;  
	virtual void nextFrame() = 0;
};

class Subject {

static 	std::vector < std::shared_ptr<Observer> > views;

public:

	virtual void init() {}

	virtual void button_loop() {}

	void addObserver(std::shared_ptr<Observer> obs);

	static	void notifyObservers(const String & status = "1");
};

