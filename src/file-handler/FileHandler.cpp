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
    vector<vector<int>> cells;
    string line;

    while (getline(file, line))
    {
        vector<int> row;
        for (char c : line)
        {
            if (c == '1' || c == '0')
            {
                row.push_back(c - '0');
            }
        }
        if (!row.empty())
        {
            cells.push_back(row);
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
    else
    {
        std::cout << "File saved successfully" << std::endl;
    }

    int width = grid->getWidth();   // Assuming Grid has getWidth()
    int height = grid->getHeight(); // Assuming Grid has getHeight()
    file << width << " " << height << '\n';

    auto cells = grid->getCells();

    for (const auto &row : cells)
    {
        for (const Cell &cell : row)
        {
            file << (cell.getType() == TypeCell::Alive ? '1' : '0') << ' ';
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
