#include "../include/Grid.hpp"
#include "../include/Cell.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
using namespace std;

Grid::Grid(int width, int height, bool isToroidal) : width(width), height(height), isToroidal(isToroidal)
{
    initGrid(width, height);
}

void Grid::initGrid(int width, int height)
{
    cells = vector<vector<Cell>>(height, vector<Cell>(width, Cell(TypeCell::Dead)));
}

void Grid::initCells(const vector<vector<int>> &tab)
{
    for (int i = 0; i < height; i++)
    {
        for (int y = 0; y < width; y++)
        {
            if (tab[i][y] == 1)
            {
                cells[i][y].setType(TypeCell::Alive);
            }
            else if (tab[i][y] == 2)
            {
                cells[i][y].setType(TypeCell::Obstacle);
            }
        }
    }
}

void Grid::initCellsRandom()
{
    srand(time(nullptr));
    int maxObstacles = width;
    int obstacleCount = 0;

    for (int i = 0; i < height; ++i)
    {
        for (int y = 0; y < width; ++y)
        {
            if (obstacleCount < maxObstacles)
            {
                int randomValue = rand() % 3;

                if (randomValue == 0)
                {
                    cells[i][y].setType(TypeCell::Dead);
                }
                else if (randomValue == 1)
                {
                    cells[i][y].setType(TypeCell::Alive);
                }
                else
                {
                    cells[i][y].setType(TypeCell::Obstacle);
                    obstacleCount++;
                }
            }
            else
            {
                int randomValue = std::rand() % 2;
                if (randomValue == 0)
                {
                    cells[i][y].setType(TypeCell::Dead);
                }
                else
                {
                    cells[i][y].setType(TypeCell::Alive);
                }
            }
        }
    }
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

/*vector<vector<int>> */ void Grid::calculateNextGen(IEvolutionStrategy *evolutionStrategy)
{
    vector<vector<int>> tab(height, vector<int>(width, 0));
    int neighbors = 0;
    if (isToroidal == false)
    {
        for (int i = 0; i < height; i++)
        {
            for (int y = 0; y < width; y++)
            {
                neighbors = 0;
                if (i == 0 || y == 0)
                {
                    for (int a = 0; a <= 1; a++)
                    {
                        for (int b = 0; b <= 1; b++)
                        {
                            if (a == 0 && b == 0)
                                continue;
                            if (cells[i + a][b].getType() == TypeCell::Alive)
                            {
                                ++neighbors;
                            }
                        }
                    }
                }
            }
        }
    }
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

void Grid::printCells() const {
    auto cells = this->getCells();
    for (const auto &row : cells)
    {
        for (const auto &cell : row)
        {
            cout << (cell.getType() == TypeCell::Alive ? "1" : "0");
        }
        cout << endl;
    }
}
