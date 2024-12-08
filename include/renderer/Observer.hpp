#pragma once

class Subject;

class Observer {
public:
    virtual void update(Subject* subject) = 0;
    virtual ~Observer() = default;
};
