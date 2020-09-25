#include "Observer.h"

void SubjectBaCh::addObserver(std::shared_ptr<Observer> obs) {

	views.push_back(obs);

}

void SubjectBaCh::notifyObservers(const String & status) {

	for (auto observer : views) {
		observer->updateDataFromBaCh(status);
	}

}
