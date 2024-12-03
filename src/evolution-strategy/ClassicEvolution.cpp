#include "../../include/evolution-strategy/ClassicEvolution.hpp"
#include "../../include/Cell.hpp"

bool ClassicEvolution::evolve(Cell* cell, int liveNeighbors) const  {
    if (cell == nullptr) {
        return false;
    }

    if (cell) { //TODO: ADJUST THIS CONDITION
        // Classic Game of Life rules:
        // A cell remains alive if it has 2 or 3 live neighbors.
        return (liveNeighbors == 2 || liveNeighbors == 3);
    } else {
        // A dead cell becomes alive if it has exactly 3 live neighbors.
        return (liveNeighbors == 3);
    }
}

ClassicEvolution::ClassicEvolution() {}
