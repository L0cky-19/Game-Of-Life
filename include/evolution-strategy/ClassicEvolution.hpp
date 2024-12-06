#pragma once
#include <string>
#include "IEvolutionStrategy.hpp"
using namespace std;

class ClassicEvolution : public IEvolutionStrategy {
private:
    string name = "Classic";
public:
    bool evolve(Cell* cell, int liveNeighbors) const override; //TODO: check if we need const
    ClassicEvolution();
    string getName() const override;
    virtual ~ClassicEvolution() override = default;
};
