#pragma once

#include <vector>
#include "./renderer/Subject.hpp" // Include Subject so Grid can inherit from it
#include "Cell.hpp"
#include "./evolution-strategy/IEvolutionStrategy.hpp"

class Grid
{
private:
    std::vector<std::vector<Cell>> cells;
    int width;
    int height;
    bool isToroidal;

public:
    Grid(int width, int height, bool isToroidal) ; //TODO: use gridData directly?

    void update(IEvolutionStrategy *evolutionStrategy);


    void initCells(const std::vector<std::vector<int>>& tab); // TODO: rename to set cells
    void initCellsRandom();

    bool /*std::vector<std::vector<int>>*/ calculateNextGen(IEvolutionStrategy *evolutionStrategy);

    // getters
    int getWidth() const;
    int getHeight() const;
    bool getIsToroidal() const;

    const std::vector<std::vector<Cell>>& getCells() const { return cells; }
    int countLiveNeighbors(int x, int y);
    void printCells() const;
    bool isGridStable(const std::vector<std::vector<TypeCell>>& nextGen) const;

    virtual ~Grid() override {
        cells.clear();
    }
};
