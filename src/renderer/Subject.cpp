#include "../../include/renderer/Subject.hpp"

void Subject::attach(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void Subject::notify() {
    for (auto& observer : observers) {
        observer->update(this);
    }
}
