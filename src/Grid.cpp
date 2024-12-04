#include "../include/Grid.hpp"
#include "../include/Cell.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
using namespace std;

Grid::Grid(int width, int height, bool isToroidal) : width(width), height(height), isToroidal(isToroidal) {
    cout << "new grid created" << width << height << isToroidal;
}


void Grid::initCells(const std::vector<std::vector<int>> &tab) { //FIXME: si on a plus de celules que dites ca va crash
    std::vector<std::vector<Cell>> newCells = {};
    for (int i = 0; i < height; i++) {
        std::vector<Cell> newRow = {};
        for (int y = 0; y < width; y++) {
            if (tab[i][y] == 1) {
                newRow.push_back(Cell(TypeCell::Alive)); // Create a Cell with type Alive
            } else if (tab[i][y] == 2) {
                newRow.push_back(Cell(TypeCell::Obstacle)); // Create a Cell with type Alive
            } else {
                newRow.push_back(Cell(TypeCell::Dead)); // Create a Cell with type Alive
            }
        }
        newCells.push_back(newRow);
    }
    cells = newCells;
}

void Grid::initCellsRandom()
{
    srand(time(nullptr));
    int maxObstacles = width;
    int obstacleCount = 0;
    std::vector<std::vector<Cell>> newCells = {};

    for (int i = 0; i < height; ++i)
    {
        std::vector<Cell> newRow = {};
        for (int y = 0; y < width; ++y)
        {
            if (obstacleCount < maxObstacles)
            {
                int randomValue = rand() % 3;

                if (randomValue == 0)
                {
                    newRow.push_back(Cell(TypeCell::Dead));
                }
                else if (randomValue == 1)
                {
                    newRow.push_back(Cell(TypeCell::Alive));
                }
                else
                {
                    newRow.push_back(Cell(TypeCell::Obstacle));
                    obstacleCount++;
                }
            }
            else
            {
                int randomValue = std::rand() % 2;
                if (randomValue == 0)
                {
                    newRow.push_back(Cell(TypeCell::Dead));
                }
                else
                {
                    newRow.push_back(Cell(TypeCell::Alive));
                }
            }
        }
        newCells.push_back(newRow);
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
bool Grid::getIsToroidal() const
{
    return isToroidal;
}


void Grid::printCells() const {
    cout << "start" << this->getHeight() << this->getWidth() << "logged";
    auto cells = this->getCells();
    cout << "2";
    for (int i = 0; i < getHeight(); ++i) // Use getHeight() instead of cells.size()
    {
        cout << "3";
        for (int j = 0; j < getWidth(); ++j) // Use getWidth() instead of cells[i].size()
        {
            cout << "4";
            cout << (cells[i][j].getType() == TypeCell::Alive ? "1" : "0");
        }
        cout << endl;
    }
}
