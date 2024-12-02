#include "include/file-handler/FileHandler.hpp"

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
            row.push_back(c == '1');
        }
        cells.push_back(row);
    }

    return Grid(cells);
}

void FileHandler::saveGridToFile(Grid *grid)
{
    ofstream file("grid_save.txt");
    if (!file.is_open())
    {
        throw runtime_error("Could not create file: grid_save.txt");
    }
    auto cells = grid->getCells();

    for (const auto &row : cells)
    {
        for (bool cell : row)
        {
            file << (cell ? '1' : '0');
        }
        file << '\n';
    }
}

Pattern FileHandler::loadPatternFromFile(string filename)
{
    return Pattern();
}

void FileHandler::savePatternToFile(Pattern pattern, string filename)
{
    // TODO: implement
}