#pragma once

#include "IEvolutionStrategy.hpp"

class HighLifeEvolution : public IEvolutionStrategy {
public:
    HighLifeEvolution();
    bool evolve(Cell* cell, int liveNeighbors) const override;
};
