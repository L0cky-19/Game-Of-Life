#include "../include/Cell.hpp"

Cell::Cell(CellType type) : type(type) {}

CellType Cell::getType() const {
    return type;
}

void Cell::setType(CellType newType) {
    type = newType;
}
