#include "../../include/file-handler/FileHandler.hpp"
#include <iostream>
#include <fstream>
#include "../../include/Game.hpp"
using namespace std;


void FileHandler::update(Subject* subject) {
    Game* game = dynamic_cast<Game*>(subject);
    if (game) {
        Grid* grid = game->getGrid();
        FileHandler fh = FileHandler();
        fh.saveGridToFile(grid);
    } else {
        throw runtime_error("Subject is not of type Game");
    }
}

vector<vector<int>> FileHandler::loadInputFromFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filename + ", please verify file path.");
    }

    int width, height;
    file >> width >> height;
    file.ignore();

    // Compter toutes les lignes non vides du fichier
    string line;
    vector<string> allLines;
    while (getline(file, line)) {
        if (!line.empty()) {
            allLines.push_back(line);
        }
    }

    if (allLines.size() != height) {
        throw runtime_error("file error: file contains incorrect number of lines.");
    }

    // Réinitialiser le fichier pour le traitement
    file.clear();
    file.seekg(0);
    file >> width >> height;
    file.ignore();

    // Traitement normal du fichier
    vector<vector<int>> cells(height, vector<int>(width));
    int lineCount = 0;

    while (getline(file, line) && lineCount < height) {
        if (line.empty()) continue;
        
        int charCount = 0;
        for (char c : line) {
            if (c == ' ') continue;
            if (charCount >= width) {
                throw runtime_error("file error: line too long.");
            }
            if (c == '1') cells[lineCount][charCount] = 1;
            else if (c == 'X') cells[lineCount][charCount] = 2;
            else if (c == '0') cells[lineCount][charCount] = 0;
            else throw runtime_error("file error: invalid character detected.");
            charCount++;
        }
        if (charCount != width) {
            throw runtime_error("file error: line too short.");
        }
        lineCount++;
    }

    return cells;
}

void FileHandler::saveGridToFile(Grid *grid)
{
    ofstream file("assets/saved-games/saved-grid.txt");
    if (!file.is_open()) {
        throw runtime_error("Could not save file: saved-grid.txt, please verify path.");
    }

    int width = grid->getWidth();
    int height = grid->getHeight();
    file << width << " " << height << '\n';

    auto cells = grid->getCells();
    for (const auto &row : cells)
    {
        for (const Cell &cell : row)
        {
            if (cell.getType() == CellType::Alive)
                file << '1' << ' ';
            else if (cell.getType() == CellType::Obstacle)
                file << 'X' << ' ';
            else
                file << '0' << ' ';
        }
        file << '\n';
    }
}

GridDimensions FileHandler::loadDimensions(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
       throw runtime_error("Could not open file: " + filename + ", please verify file path.");
    } 

    GridDimensions dims;
    file >> dims.width >> dims.height;
    return dims;
}
