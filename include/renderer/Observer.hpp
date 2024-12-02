#ifndef OBSERVER_HPP
#define OBSERVER_HPP

class Subject;  // Forward declaration

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(Subject* subject) = 0;
};

#endif // OBSERVER_HPP
