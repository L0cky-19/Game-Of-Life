#include "../../include/evolution-strategy/HighLifeEvolution.hpp"
#include "../../include/Cell.hpp"

bool HighLifeEvolution::evolve(Cell *cell, int liveNeighbors) const {
    if (cell == nullptr) {
        return false;
    }
    if (cell->getType() == CellType::Alive) {
        return (liveNeighbors == 2 || liveNeighbors == 3);
    } else {
        return (liveNeighbors == 3 || liveNeighbors == 6);
    }
}

HighLifeEvolution::HighLifeEvolution() {}

string HighLifeEvolution::getName() const {
    return "Highlife";
}
