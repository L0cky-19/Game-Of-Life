#include <C:/msys64/mingw64/include/gtest/gtest.h>
#include "../include/Grid.hpp"
#include "../include/evolution-strategy/ClassicEvolution.hpp"
#include <iostream>

// Macro pour une sortie colorée

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
        {0, 1, 0},  // Dead, Alive, Dead
        {1, 1, 1},  // Alive, Alive, Alive
        {0, 1, 0}}; // Dead, Alive, Dead

    grid.initCells(testGrid);
    IEvolutionStrategy *strategy = new ClassicEvolution();

    grid.calculateNextGen(strategy);
    auto cells = grid.getCells();

    // Expected result: all cells around center become alive, center dies
    vector<vector<int>> expectedGrid = {
        {1, 1, 1}, // All alive due to having 3 neighbors
        {1, 0, 1}, // Center dies due to having >3 neighbors
        {1, 1, 1}};

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

// New test to check if a cell becomes alive properly
TEST_F(GridTest, CellDeath)
{
    Grid grid(3, 3, false);
    vector<vector<int>> testGrid = {
        {0, 0, 0},  // All Dead
        {0, 1, 0},  // Center Alive
        {0, 0, 0}}; // All Dead

    grid.initCells(testGrid);
    IEvolutionStrategy *strategy = new ClassicEvolution();

    grid.calculateNextGen(strategy);
    auto cells = grid.getCells();

    // Expected result: cell dies as it has no neighbors
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
