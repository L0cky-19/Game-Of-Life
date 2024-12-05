#include "../../include/file-handler/FileHandler.hpp"
#include <iostream>
#include <fstream>

using namespace std;

vector<vector<int>> FileHandler::loadInputFromFile(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("Could not open file: " + filename);
    }

    int width, height;
    file >> width >> height;
    file.ignore();

    vector<vector<int>> cells(height, vector<int>(width));
    string line;

    for (int i = 0; i < height; i++)
    {
        getline(file, line);
        int j = 0;
        for (char c : line)
        {
            if (c == '1' || c == '0')
            {
                cells[i][j++] = c - '0';
            }
        }
    }

    return cells;
}

void FileHandler::saveGridToFile(Grid *grid)
{
    ofstream file("/Users/azuka/Documents/grid_save.txt");
    if (!file.is_open())
    {
        throw runtime_error("Could not create file: grid_save.txt");
    }

    int width = grid->getWidth();   // Assuming Grid has getWidth()
    int height = grid->getHeight(); // Assuming Grid has getHeight()
    file << width << " " << height << '\n';

    auto cells = grid->getCells();

    for (const auto &row : cells)
    {
        for (const Cell &cell : row)
        {
            file << (cell.getType() == TypeCell::Alive ? '1' : '0');
        }
        file << '\n';
    }
}

// Pattern FileHandler::loadPatternFromFile(string filename)
// {
//     return Pattern();
// }

// void FileHandler::savePatternToFile(Pattern pattern, string filename)
// {
//     // TODO: implement
// }

GridDimensions FileHandler::loadDimensions(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("Could not open file: " + filename);
    }

    GridDimensions dims;
    file >> dims.width >> dims.height;
    return dims;
}
