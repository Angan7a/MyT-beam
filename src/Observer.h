#pragma once

#include <vector>
#include <memory>
#include <WString.h>
#include "PacketGPS.h"

class Observer;

class ObserverAndSubject {
public:
	virtual void updateDataFromSubjectGPS(const PacketGPS & packetGPS) {}
	
	virtual void updateDataFromSubjectBatCh(const String & status) {}

	virtual void updateDataFromSubjectLora(const String & message, double rssi) {}

	virtual void updateDataFromSubjectButton() {}

	virtual void init() {}

	virtual void loop() {}  

	virtual void received() {}

	virtual void send(const String & message) {}

	virtual void addObserver(std::shared_ptr<ObserverAndSubject> obs) {}

	virtual ~ObserverAndSubject() {}

};
//============================================================================
class Observer : virtual public ObserverAndSubject {

public:
	virtual void updateDataFromSubjectGPS(const PacketGPS & packetGPS) {}
	
	virtual void updateDataFromSubjectBatCh(const String & status) {}

	virtual void updateDataFromSubjectLora(const String & message, double rssi) {}

	virtual void updateDataFromSubjectButton() {}

	virtual void init() = 0;

	virtual void loop() = 0;  

	virtual void received() {}

	virtual void send(const String & message) {}

	virtual ~Observer() {}
};

//============================================================================
class SubjectForObserv : virtual public ObserverAndSubject{

protected:

	//static std::vector < std::shared_ptr<Observer> > views;
	std::vector < std::shared_ptr<ObserverAndSubject> > views;
	
public:

	//static void addObserver(std::shared_ptr<Observer> obs);
	void addObserver(std::shared_ptr<ObserverAndSubject> obs);

	virtual void scanDevices() {}

	virtual void setAxp192() {}
	
	virtual void wasIRQ() {}

	virtual void loop() {}

	virtual void notifyObserversBatCh(const String & status) {}

	void notifyObserversButton();
	
	virtual void notifyObserversGPS(const PacketGPS & packetGPS) {}

	virtual void notifyObserversLora(const String & message, double rssi) {}

	virtual ~SubjectForObserv() {}
};


//============================================================================
class SubjectBatCh : public SubjectForObserv {
public:

	void notifyObserversBatCh(const String & status);

};	

//============================================================================
class SubjectGPS : public SubjectForObserv {
public:

	void notifyObserversGPS(const PacketGPS & packetGPS);

};	

//============================================================================
class SubjectButton : public SubjectForObserv {
};	

//============================================================================
class SubjectLora : public SubjectForObserv {
public:

	void notifyObserversLora(const String & message, double rssi);
};	
