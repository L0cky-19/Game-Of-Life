#pragma once
#include <memory>
#include "Observer.hpp"
#include <vector>

class Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers;
public:
    void attach(std::shared_ptr<Observer> observer);
    void detach(std::shared_ptr<Observer> observer);
    void notify();
    virtual ~Subject() = default;
};
