#include <C:/msys64/mingw64/include/gtest/gtest.h>
#include "../include/Grid.hpp"
#include "../include/evolution-strategy/ClassicEvolution.hpp"
#include <iostream>

// Macro pour une sortie colorée
#define GTEST_COUT std::cerr << "[   INFO   ] \033[1;36m"
#define GTEST_COUT_END "\033[0m" << std::endl

class GridTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(GridTest, CellEvolution)
{
    Grid grid(3, 3, false);
    vector<vector<int>> testGrid = {
        {0, 1, 0},  // Dead, Alive, Dead
        {1, 1, 1},  // Alive, Alive, Alive
        {0, 1, 0}}; // Dead, Alive, Dead

    grid.initCells(testGrid);
    IEvolutionStrategy *strategy = new ClassicEvolution();

    grid.printCells();

    grid.calculateNextGen(strategy);
    auto cells = grid.getCells();

    grid.printCells();

    // Expected result: all cells around center become alive, center dies
    vector<vector<int>> expectedGrid = {
        {1, 1, 1}, // All alive due to having 3 neighbors
        {1, 0, 1}, // Center dies due to having >3 neighbors
        {1, 1, 1}};

    // Verify each cell matches expected state
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            bool isAlive = cells[i][j].getType() == CellType::Alive;
            EXPECT_EQ(isAlive, expectedGrid[i][j] == 1);
        }
    }

    delete strategy;
}
