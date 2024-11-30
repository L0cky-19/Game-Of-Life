#pragma once

#include "IEvolutionStrategy.h"

class ClassicEvolution : public IEvolutionStrategy {
public:
    bool evolve(Cell* cell, int liveNeighbors)
};
