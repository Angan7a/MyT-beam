#include "Observer.h"

void Subject::addObserver(std::shared_ptr<Observer> obs) {

	views.push_back(obs);

}

std::vector < std::shared_ptr<Observer> > Subject::views;

void Subject::notifyObservers(const String & status) {

	for (auto observer : views) {
		observer->updateDataFromBaCh(status);
	}

}
