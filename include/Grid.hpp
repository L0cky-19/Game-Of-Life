#pragma once

#include <vector>
#include "./renderer/Subject.hpp" // Include Subject so Grid can inherit from it
#include "Cell.hpp"
#include "./evolution-strategy/IEvolutionStrategy.hpp"

class Grid : public Subject
{ // Now Grid inherits from Subject
private:
    std::vector<std::vector<Cell>> cells;
    int width;
    int height;
    bool isToroidal;

public:
    Grid(int width, int height, bool isToroidal = false);

    void update(IEvolutionStrategy *evolutionStrategy);

    void initGrid(int width, int height);

    void initCells(const std::vector<std::vector<int>> &tab);
    void initCellsRandom();

    void /*std::vector<std::vector<int>>*/ calculateNextGen(IEvolutionStrategy *evolutionStrategy);

    // getters
    int getWidth() const;
    int getHeight() const;

    const std::vector<std::vector<Cell>>& getCells() const { return cells; }
};
