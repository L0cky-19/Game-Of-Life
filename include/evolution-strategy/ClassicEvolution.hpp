#pragma once

#include "IEvolutionStrategy.hpp"

class ClassicEvolution : public IEvolutionStrategy {
public:
    bool evolve(Cell* cell, int liveNeighbors) const override; //TODO: check if we need const
    ClassicEvolution();
};
