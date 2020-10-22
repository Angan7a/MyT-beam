#include "Observer.h"

//std::vector<std::shared_ptr<Observer>> SubjectForObserv::views;

void SubjectForObserv::addObserver(std::shared_ptr<ObserverAndSubject> obs) {

	views.push_back(obs);
}

//void SubjectForObserv::notifyObservers(const String & status) {

//	for (auto observer : views) {
//		observer->updateDataFromSubject(status);
//	}
//}

//std::vector<std::shared_ptr<Observer>> SubjectBatCh::views;

void SubjectBatCh::notifyObserversBatCh(const String & status) {

	for (auto observer : views) {
		observer->updateDataFromSubjectBatCh(status);
	}
}

void SubjectForObserv::notifyObserversButton() {

	for (auto observer : views) {
		observer->updateDataFromSubjectButton();
	}
}

void SubjectGPS::notifyObserversGPS(const PacketGPS & packetGPS) {

	for (auto observer : views) {
		observer->updateDataFromSubjectGPS(packetGPS);
	}
}

void SubjectLora::notifyObserversLora(const String & message, double rssi) {

	for (auto observer : views) {
		observer->updateDataFromSubjectLora(message, rssi);
	}
}
