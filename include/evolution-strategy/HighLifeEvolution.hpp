#pragma once

#include "IEvolutionStrategy.h"

class HighLifeEvolution : public IEvolutionStrategy {
public:
    bool evolve(Cell* cell, int liveNeighbors)
};
