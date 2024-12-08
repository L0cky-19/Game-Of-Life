#include <C:/msys64/mingw64/include/gtest/gtest.h>
#include "../include/Grid.hpp"
#include "../include/evolution-strategy/ClassicEvolution.hpp"
#include <iostream>

class GridTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(GridTest, CellBirth)
{
    Grid grid(3, 3, false);
    vector<vector<int>> testGrid = {
        {1, 1, 0},
        {1, 0, 0},
        {0, 0, 0}};

    grid.initCells(testGrid);
    IEvolutionStrategy *strategy = new ClassicEvolution();

    grid.calculateNextGen(strategy);
    auto cells = grid.getCells();

    // Expected result: Center becomes alive due to having 3 neighbours
    vector<vector<int>> expectedGrid = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 0}};

    // Verify each cell matches expected state
    bool allMatch = true; // Track if all cells match
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            bool isAlive = cells[i][j].getType() == CellType::Alive;
            if (isAlive != (expectedGrid[i][j] == 1)) {
                allMatch = false; // Set to false if any cell does not match
            }
            EXPECT_EQ(isAlive, expectedGrid[i][j] == 1);
        }
    }


    delete strategy;
}


TEST_F(GridTest, CellDeath)
{
    Grid grid(3, 3, false);
    vector<vector<int>> testGrid = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}};

    grid.initCells(testGrid);
    IEvolutionStrategy *strategy = new ClassicEvolution();

    grid.calculateNextGen(strategy);
    auto cells = grid.getCells();

    // Expected result: Center Cell dies as it has no neighbors
    vector<vector<int>> expectedGrid = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};

    // Verify each cell matches expected state
    bool allMatch = true; // Track if all cells match
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            bool isAlive = cells[i][j].getType() == CellType::Alive;
            if (isAlive != (expectedGrid[i][j] == 1)) {
                allMatch = false; // Set to false if any cell does not match
            }
            EXPECT_EQ(isAlive, expectedGrid[i][j] == 1);
        }
    }

    delete strategy;
}
