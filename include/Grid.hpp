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
    void initCells(const std::vector<std::vector<int>> &tab);
    void initCellsRandom();
    bool calculateNextGen(IEvolutionStrategy *evolutionStrategy);
    // getters
    int getWidth() const;
    int getHeight() const;
    bool getIsToroidal() const;
    const std::vector<std::vector<Cell>> &getCells() const;
    int countLiveNeighbors(int x, int y);
    void printCells() const;
    bool isGridStable(const std::vector<std::vector<CellType>>& nextGen) const;

    virtual ~Grid() {
        cells.clear();
    }
};
