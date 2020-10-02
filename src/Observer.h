#pragma once

#include <vector>
#include <memory>
#include <WString.h>
#include "PacketGPS.h"

class Observer {

public:
	virtual void updateDataFromSubjectGPS(const PacketGPS & packetGPS) {}
	
	virtual void updateDataFromSubjectBatCh(const String & status) {}

	virtual void updateDataFromSubjectButton() {}

	virtual void init() = 0;

	virtual void loop() = 0;  

	virtual ~Observer() {}
};


class SubjectForObserv {

protected:

	static std::vector < std::shared_ptr<Observer> > views;
	
public:

	static void addObserver(std::shared_ptr<Observer> obs);

	virtual void scanDevices() {}

	virtual void setAxp192() {}
	
	virtual void wasIRQ() {}

	virtual void loop() {}

	virtual void notifyObserversBatCh(const String & status) {}

	static void notifyObserversButton(); //it is not the best solution ...
	
	void notifyObserversGPS(const PacketGPS & packetGPS);

	virtual ~SubjectForObserv() {}
};


class SubjectBatCh : public SubjectForObserv {
public:

	void notifyObserversBatCh(const String & status);

};	

class SubjectGPS : public SubjectForObserv {
public:

	void notifyObserversGPS(const PacketGPS & packetGPS);

};	

class SubjectButton : public SubjectForObserv {
};	
