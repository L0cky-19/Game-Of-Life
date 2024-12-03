#pragma once

class Subject;  // Forward declaration

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(Subject* subject) = 0;
};
