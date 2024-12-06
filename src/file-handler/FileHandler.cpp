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
            if (c == '1')
                cells[i][j++] = 1;
            else if (c == '2')
                cells[i][j++] = 2;
            else if (c == '0')
                cells[i][j++] = 0;
        }
    }

    return cells;
}

void FileHandler::saveGridToFile(Grid *grid)
{
    ofstream file("assets/saveGridToFile/updateGrid.txt");
    if (!file.is_open())
    {
        throw runtime_error("Could not saved file: updateGrid.txt");
    }

    int width = grid->getWidth();
    int height = grid->getHeight();
    file << width << " " << height << '\n';

    auto cells = grid->getCells();
    for (const auto &row : cells)
    {
        for (const Cell &cell : row)
        {
            if (cell.getType() == TypeCell::Alive)
                file << '1';
            else if (cell.getType() == TypeCell::Obstacle)
                file << '2';
            else
                file << '0';
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
