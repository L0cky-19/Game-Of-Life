#include "../include/Grid.hpp"
#include "../include/Cell.hpp"
#include "../include/evolution-strategy/ClassicEvolution.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
using namespace std;

Grid::Grid(int width, int height, bool isToroidal) : width(width), height(height), isToroidal(isToroidal) {}

void Grid::initCells(const std::vector<std::vector<int>> &tab) { // FIXME: si on a plus de celules que dites ca va crash
    std::vector<std::vector<Cell>> newCells = {};
    for (int i = 0; i < height; i++)
    {
        std::vector<Cell> newRow = {};
        for (int y = 0; y < width; y++)
        {
            if (tab[i][y] == 1)
            {
                newRow.push_back(Cell(CellType::Alive));
            }
            else if (tab[i][y] == 2)
            {
                newRow.push_back(Cell(CellType::Obstacle));
            }
            else
            {
                newRow.push_back(Cell(CellType::Dead));
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
            newRow.push_back(rand() % 2 == 0 ? CellType::Dead : CellType::Alive);
        }
        newCells.push_back(newRow);
    }

    for (int i = 0; i < numObstacles; i++)
    {
        int randY = rand() % height;
        int randX = rand() % width;
        newCells[randY][randX] = Cell(CellType::Obstacle);
    }
    cells = newCells;
}


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

            if (cells[ny][nx].getType() == CellType::Alive)
            {
                count++;
            }
        }
    }
    return count;
}

bool Grid::isGridStable(const vector<vector<CellType>> &nextGen) const
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
    vector<vector<CellType>> nextGen(height, vector<CellType>(width, CellType::Dead));
    int neighbors = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (cells[y][x].getType() == CellType::Obstacle)
            {
                nextGen[y][x] = CellType::Obstacle;
            }
        }
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (cells[y][x].getType() != CellType::Obstacle)
            {
                neighbors = countLiveNeighbors(x, y);
                if (evolutionStrategy->evolve(&cells[y][x], neighbors))
                {
                    nextGen[y][x] = CellType::Alive;
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


int Grid::getWidth() const {
    return width;
}

int Grid::getHeight() const {
    return height;
}
bool Grid::getIsToroidal() const {
    return isToroidal;
}

void Grid::printCells() const
{
    auto cells = this->getCells();
    for (int i = 0; i < getHeight(); ++i)
    {
        for (int j = 0; j < getWidth(); ++j)
        {
            if (cells[i][j].getType() == CellType::Alive) {
                cout << "1 ";
            } else if (cells[i][j].getType() == CellType::Obstacle) {
                cout << "X ";
            } else {
                cout << "0 ";
            }
        }
        cout << endl;
    }
}

const std::vector<std::vector<Cell>> &Grid::getCells() const {
    return cells;
}
