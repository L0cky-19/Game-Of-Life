#include "../../include/evolution-strategy/HighLifeEvolution.hpp"
#include "../../include/Cell.hpp"

bool HighLifeEvolution::evolve(Cell* cell, int liveNeighbors) {
    if (cell == nullptr) {
        return false;
    }

    if (cell->isAlive()) {
        // HighLife rules for live cells:
        // A cell remains alive if it has 2 or 3 live neighbors.
        return (liveNeighbors == 2 || liveNeighbors == 3);
    } else {
        // HighLife rules for dead cells:
        // A dead cell becomes alive if it has exactly 3 or 6 live neighbors.
        return (liveNeighbors == 3 || liveNeighbors == 6);
    }
}
