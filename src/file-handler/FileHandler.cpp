#include "include/file-handler/FileHandler.hpp"

#include <fstream>

using namespace std;

Grid FileHandler::loadGridFromFile(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("Could not open file: " + filename);
    }
    vector<vector<bool>> cells;
    string line;

    while (getline(file, line))
    {
        vector<bool> row;
        for (char c : line)
        {
            if (c == '1' || c == '0')
            {
                row.push_back(c == '1');
            }
        }
        if (!row.empty())
        {
            cells.push_back(row);
        }
    }

    return Grid(cells.size(), cells[0].size(), false);
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