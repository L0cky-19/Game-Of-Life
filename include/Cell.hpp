#pragma once

enum class TypeCell { //TODO: rename
    Alive,
    Dead,
    Obstacle
};

class Cell {
private:
    TypeCell type;

public:
    Cell(TypeCell type) : type(type) {}
    TypeCell getType() const { return type; }
    void setType(TypeCell newType) { type = newType; }
};
