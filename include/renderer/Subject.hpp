#include <memory>
#include "Observer.hpp"
#include <vector>
#pragma once

//TODO: changer l'endroit, il ne devrait pas être ici

class Subject { //TODO: export this design pattern
public:
    virtual ~Subject() = default;

    // Attach an observer to the subject
    void attach(std::shared_ptr<Observer> observer);

    // Detach an observer from the subject
    void detach(std::shared_ptr<Observer> observer);

    // Notify all registered observers of a state change
    void notify();

private:
    std::vector<std::shared_ptr<Observer>> observers;  // List of observers
};
