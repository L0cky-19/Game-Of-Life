#pragma once
#include <vector>
#include "../../../include/renderer/Observer.hpp"

class Subject {
public:
    virtual ~Subject() = default;
    virtual void attach(Observer* observer) = 0;
    virtual void notify() = 0;
};

namespace testing {
    class MockSubject : public Subject {
    public:
        void attach(Observer* observer) override {
            observers.push_back(observer);
        }
        
        void notify() override {
            for (Observer* observer : observers) {
                observer->update(this);
            }
        }
    
    protected:
        std::vector<Observer*> observers;
    };
} 