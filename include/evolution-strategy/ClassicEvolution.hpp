#pragma once
#include <string>
#include "IEvolutionStrategy.hpp"
using namespace std;

class ClassicEvolution : public IEvolutionStrategy {
private:
    string name = "Classic";
public:
    ClassicEvolution();
    bool evolve(Cell* cell, int liveNeighbors) const override;
    string getName() const override;
    virtual ~ClassicEvolution() override = default;
};
