#pragma once

#include <vector>
using namespace std;

#include "Cell.hpp"
#include "./evolution-strategy/IEvolutionStrategy.hpp"
//#include "Pattern.cpp"

class Grid {
private:
    vector<vector<Cell>> cells;
    int width;
    int height;
    bool isToroidal;
public:
    Grid(int width, int height, bool isToroidal = false);

    void update(IEvolutionStrategy* evolutionStrategy);

    void initGrid(int width, int height);

    void initCells(const vector<vector<int>>& tab);
    void initCellsRandom();

    vector<vector<int>> calculateNextGeneration(IEvolutionStrategy* evolutionStrategy);

    //void applyPattern(const Pattern& pattern, const vector<int>& position);
};
