#include "Observer.h"

std::vector<std::shared_ptr<Observer>> SubjectForObserv::views;

void SubjectForObserv::addObserver(std::shared_ptr<Observer> obs) {

	views.push_back(obs);
}

void SubjectForObserv::notifyObservers(const String & status) {

	for (auto observer : views) {
		observer->updateDataFromSubject(status);
	}
}

