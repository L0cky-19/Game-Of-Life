#include "../../include/renderer/ConsoleRenderer.hpp"
#include "../../include/Game.hpp"
#include <iostream>
using namespace std;


void ConsoleRenderer::render(Grid *grid) {
    system("cls"); // FIXME: detect os ? wont work for macos

    if (!grid)
        return;

    const auto &cells = grid->getCells();
    for (int y = 0; y < grid->getHeight(); y++)
    {
        for (int x = 0; x < grid->getWidth(); x++)
        {
            if (cells[y][x].getType() == CellType::Alive)
                std::cout << "1 ";
            else if (cells[y][x].getType() == CellType::Obstacle)
                std::cout << "X ";
            else
            {
                std::cout << "0 ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

string ConsoleRenderer::getName() const {
    return "Console";
}
