#pragma once

#include <vector>
#include <memory>
#include <WString.h>

class Observer {

public:
	virtual void updateDataFromSubject(const String & status) = 0;

	virtual void init() = 0;

	virtual void loop() = 0;  

};


class SubjectForObserv {

protected:

	static std::vector < std::shared_ptr<Observer> > views;

public:

	static void addObserver(std::shared_ptr<Observer> obs);

	static void notifyObservers(const String & status = "");

	virtual void scanDevices() {}

	virtual void setAxp192() {}
	
	virtual void wasIRQ() {}

	virtual void loop() {}
};

