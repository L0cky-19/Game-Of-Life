#include "include/Cell.hpp"

Cell::Cell(TypeCell type) : type(type) {}

TypeCell Cell::getType() const {
    return type;
}

void Cell::setType(TypeCell newType) {
    type = newType;
}
