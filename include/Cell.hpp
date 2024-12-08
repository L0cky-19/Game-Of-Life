#pragma once

enum class CellType {
    Alive,
    Dead,
    Obstacle
};

class Cell {
private:
    CellType type;
public:
    Cell() = default;
    Cell(CellType type);
    CellType getType() const;
    void setType(CellType newType);
    virtual ~Cell() = default;
};
