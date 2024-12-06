#include "../include/Grid.hpp"
#include "../include/Cell.hpp"
#include "../include/evolution-strategy/ClassicEvolution.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <gtest/gtest.h>
using namespace std;

Grid::Grid(int width, int height, bool isToroidal) : width(width), height(height), isToroidal(isToroidal) {}

void Grid::initCells(const std::vector<std::vector<int>> &tab)
{ // FIXME: si on a plus de celules que dites ca va crash
    std::vector<std::vector<Cell>> newCells = {};
    for (int i = 0; i < height; i++)
    {
        std::vector<Cell> newRow = {};
        for (int y = 0; y < width; y++)
        {
            if (tab[i][y] == 1)
            {
                newRow.push_back(Cell(TypeCell::Alive)); // Create a Cell with type Alive
            }
            else if (tab[i][y] == 2)
            {
                newRow.push_back(Cell(TypeCell::Obstacle)); // Create a Cell with type Alive
            }
            else
            {
                newRow.push_back(Cell(TypeCell::Dead)); // Create a Cell with type Alive
            }
        }
        newCells.push_back(newRow);
    }
    cells = newCells;
}

void Grid::initCellsRandom()
{
    std::vector<std::vector<Cell>> newCells = {};
    srand(time(nullptr));
    // Calculate number of obstacles (1 per 100 cells)
    int totalCells = width * height;
    int numObstacles = totalCells / 100;
    if (numObstacles < 1)
        numObstacles = 1;

    // First create grid with alive/dead cells
    for (int y = 0; y < height; y++)
    {
        std::vector<Cell> newRow = {};
        for (int x = 0; x < width; x++)
        {
            newRow.push_back(rand() % 2 == 0 ? TypeCell::Dead : TypeCell::Alive);
        }
        newCells.push_back(newRow);
    }

    for (int i = 0; i < numObstacles; i++)
    {
        int randY = rand() % height;
        int randX = rand() % width;
        newCells[randY][randX] = Cell(TypeCell::Obstacle);
    }
    cells = newCells;
}

/*
void Grid::applyPattern(const Pattern& pattern, const vector<int>& position){
    if ( isToroidal == false &&  (position[0]> height || position[1]> width)){}
    else if (isToroidal == false){
        for (int i = position[0]; i < height; ++i) {
            for (int y = position[1]; y < width; ++y) {
                if ( cells[i][y].getType() != pattern[position[0]-i][position[1]-y].getType()){
                    cells[i][y].setType(pattern[position[0]-i][position[1]-y].getType());
                }
            }
        }
    }
    else if (isToroidal == true){
        for (int i = 0; i < position[0]; ++i) {
            for (int y = 0; y < position[1]; ++y) {
                if ( cells[(i+position[0])%height][(y+position[1])%width].getType() != pattern[i][y].getType()){
                    cells[(i+position[0])%height][(y+position[1])%width].setType(pattern[i][y].getType());
                }
            }
        }
    }
}
*/
int Grid::countLiveNeighbors(int x, int y)
{
    int count = 0;
    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            if (dx == 0 && dy == 0)
                continue;

            int nx = x + dx;
            int ny = y + dy;

            if (isToroidal)
            {
                nx = (nx + width) % width;
                ny = (ny + height) % height;
            }
            else if (nx < 0 || nx >= width || ny < 0 || ny >= height)
            {
                continue;
            }

            if (cells[ny][nx].getType() == TypeCell::Alive)
            {
                count++;
            }
        }
    }
    return count;
}

bool Grid::isGridStable(const vector<vector<TypeCell>> &nextGen) const
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (nextGen[y][x] != cells[y][x].getType())
            {
                return false;
            }
        }
    }
    return true;
}

bool Grid::calculateNextGen(IEvolutionStrategy *evolutionStrategy)
{
    vector<vector<TypeCell>> nextGen(height, vector<TypeCell>(width, TypeCell::Dead));
    int neighbors = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (cells[y][x].getType() == TypeCell::Obstacle)
            {
                nextGen[y][x] = TypeCell::Obstacle;
            }
        }
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (cells[y][x].getType() != TypeCell::Obstacle)
            {
                neighbors = countLiveNeighbors(x, y);
                if (evolutionStrategy->evolve(&cells[y][x], neighbors))
                {
                    nextGen[y][x] = TypeCell::Alive;
                }
            }
        }
    }

    if (isGridStable(nextGen))
    {
        std::cout << "Le jeu est stable" << std::endl;
        return true;
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            cells[y][x].setType(nextGen[y][x]);
        }
    }
    return false;
}
void Grid::update(IEvolutionStrategy *evolutionStrategy)
{
    vector<vector<int>> tab;
    /*
    tab = calculateNextGen(evolutionStrategy);
    for (int i = 0;i< height; i++){
        for (int y = 0;y< width; y++){
            if ( tab[i][y] == 0 && cells[i][y].getType() != TypeCell::Dead){
                cells[i][y].setType(TypeCell::Dead);
            }
            else if ( tab[i][y] == 1 && cells[i][y].getType() != TypeCell::Alive){
                cells[i][y].setType(TypeCell::Alive);
            }
        }
    }*/
}

int Grid::getWidth() const
{
    return width;
}

int Grid::getHeight() const
{
    return height;
}
bool Grid::getIsToroidal() const
{
    return isToroidal;
}

void Grid::printCells() const
{
    auto cells = this->getCells();
    for (int i = 0; i < getHeight(); ++i) // Use getHeight() instead of cells.size()
    {
        for (int j = 0; j < getWidth(); ++j) // Use getWidth() instead of cells[i].size()
        {
            cout << (cells[i][j].getType() == TypeCell::Alive ? "1" : "0");
        }
        cout << endl;
    }
}

void Grid::testCellBehavior()
{
    Grid grid(3, 3, false);
    vector<vector<int>> testGrid = {
        {0, 1, 0},
        {1, 1, 1},
        {0, 1, 0}};

    grid.initCells(testGrid);
    IEvolutionStrategy *strategy = new ClassicEvolution();

    bool success = grid.calculateNextGen(strategy);

    delete strategy;
    cout << "Cell behavior test completed" << endl;
}

TEST(GridTest, CellEvolution)
{
    Grid grid(3, 3, false);
    vector<vector<int>> testGrid = {
        {0, 1, 0},
        {1, 1, 1},
        {0, 1, 0}};

    grid.initCells(testGrid);
    IEvolutionStrategy *strategy = new ClassicEvolution();

    grid.calculateNextGen(strategy);
    auto cells = grid.getCells();

    vector<vector<int>> expectedGrid = {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            bool isAlive = cells[i][j].getType() == TypeCell::Alive;
            EXPECT_EQ(isAlive, expectedGrid[i][j] == 1);
        }
    }

    delete strategy;
}
