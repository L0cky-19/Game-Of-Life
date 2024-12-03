#pragma once
#include "MockSubject.hpp"

class Grid : public Subject {
public:
    virtual ~Grid() = default;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual bool isCellAlive(int x, int y) const = 0;
};

namespace testing {
    class MockGrid : public Grid {
    public:
        MockGrid(int width = 30, int height = 20) 
            : width_(width), height_(height) {}
        
        void attach(Observer* observer) override {
            observers.push_back(observer);
        }
        
        void notify() override {
            for (Observer* observer : observers) {
                observer->update(this);
            }
        }
        
        int getWidth() const override { return width_; }
        int getHeight() const override { return height_; }
        bool isCellAlive(int x, int y) const override { return false; }

    private:
        int width_;
        int height_;
        std::vector<Observer*> observers;
    };
} 