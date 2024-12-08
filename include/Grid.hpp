#pragma once
#include <vector>
#include "Cell.hpp"
#include "./evolution-strategy/IEvolutionStrategy.hpp"

class Grid {
private:
    std::vector<std::vector<Cell>> cells;
    int width;
    int height;
    bool isToroidal;
public:
    Grid(int width, int height, bool isToroidal); // TODO: use gridData directly?
    void update(IEvolutionStrategy *evolutionStrategy);
    void initCells(const std::vector<std::vector<int>> &tab); // TODO: rename to set cells
    void initCellsRandom();
    bool calculateNextGen(IEvolutionStrategy *evolutionStrategy);
    // getters
    int getWidth() const;
    int getHeight() const;
    bool getIsToroidal() const;
    const std::vector<std::vector<Cell>> &getCells() const { return cells; } // TODO: implement in cpp
    int countLiveNeighbors(int x, int y);
    void printCells() const;
    bool isGridStable(const std::vector<std::vector<TypeCell>>& nextGen) const;

    virtual ~Grid() {
        cells.clear();
    }
};
