#include "../../include/renderer/ConsoleRenderer.hpp"
#include "../../include/Game.hpp"
#include <iostream>
using namespace std;


void ConsoleRenderer::render(Grid *grid) {
    system("cls");

    if (!grid)
        return;

    const auto &cells = grid->getCells();
    for (int y = 0; y < grid->getHeight(); y++)
    {
        for (int x = 0; x < grid->getWidth(); x++)
        {
            if (cells[y][x].getType() == CellType::Alive)
                std::cout << "\033[32m1 \033[0m";
            else if (cells[y][x].getType() == CellType::Obstacle)
                std::cout << "\033[31mX \033[0m";
            else
            {
                std::cout << "0 ";
            }
        }
        std::cout << std::endl;
    }
}

string ConsoleRenderer::getName() const {
    return "Console";
}
