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
    Cell() = default;
    Cell(TypeCell type);
    TypeCell getType() const;
    void setType(TypeCell newType);
    virtual ~Cell() = default;
};
