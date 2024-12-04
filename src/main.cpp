#include <iostream>
#include "../include/Game.hpp"

#include "../include/file-handler/FileHandler.hpp"

// TODO: check if Interfaces keep their name if they are not virtual anymore?
int main()
{
    // Game game;
    // game.setup();
    // game.run();

    FileHandler fileHandler;
    Grid grid = fileHandler.loadGridFromFile("/Users/azuka/Documents/grid.txt");

    auto cells = grid.getCells();
    for (const auto &row : cells)
    {
        for (const auto &cell : row)
        {
            cout << (cell.getType() == TypeCell::Alive ? "1" : "0");
        }
        cout << endl;
    }

    fileHandler.saveGridToFile(&grid);
}
