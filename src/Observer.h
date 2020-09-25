#pragma once

#include <vector>
#include <memory>
#include <WString.h>

class Observer {

public:
	virtual void updateDataFromBaCh(const String & status) = 0;
	virtual void init() = 0;
	virtual void loop() = 0;  
};

class SubjectBaCh {

	std::vector < std::shared_ptr<Observer> > views;

public:

	void addObserver(std::shared_ptr<Observer> obs);

	void notifyObservers(const String & status);
};

