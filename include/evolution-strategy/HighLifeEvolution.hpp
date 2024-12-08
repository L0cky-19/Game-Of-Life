#pragma once

#include "IEvolutionStrategy.hpp"
#include <string>
using namespace std;

class HighLifeEvolution : public IEvolutionStrategy {
private:
    string name = "High Life";
public:
    HighLifeEvolution();
    bool evolve(Cell* cell, int liveNeighbors) const override;
    string getName() const override;
    virtual ~HighLifeEvolution() override = default;
};
