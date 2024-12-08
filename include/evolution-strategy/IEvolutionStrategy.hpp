#pragma once
#include "../Cell.hpp"
#include <string>
using namespace std;

class IEvolutionStrategy {
public:
    virtual bool evolve(Cell* cell,int liveNeighbors) const = 0;
    virtual string getName() const = 0;
    virtual ~IEvolutionStrategy() = default;
};
