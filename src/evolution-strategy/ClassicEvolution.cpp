#include "../../include/evolution-strategy/ClassicEvolution.hpp"
#include "../../include/Cell.hpp"

bool ClassicEvolution::evolve(Cell *cell, int liveNeighbors) const {
    if (cell == nullptr || cell->getType() == CellType::Obstacle) {
        return false;
    }
    if (cell->getType() == CellType::Alive) {
        return (liveNeighbors == 2 || liveNeighbors == 3);
    } else {
        return (liveNeighbors == 3);
    }
}

ClassicEvolution::ClassicEvolution() {}

string ClassicEvolution::getName() const {
    return "Classic";
}
