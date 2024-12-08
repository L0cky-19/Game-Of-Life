#include "../../include/renderer/ConsoleRenderer.hpp"
#include "../../include/Game.hpp"
#include <iostream>
using namespace std;

void ConsoleRenderer::update(Subject *subject) {
    Game *game = dynamic_cast<Game*>(subject);
    if (game) {
        render(game->getGrid());
    } else {
        // Handle the case where the subject is not a Game
        std::cerr << "Error: Subject is not of type Game." << std::endl;
    }
}

void ConsoleRenderer::render(Grid *grid) {
    system("cls"); // FIXME: detect os ? wont work for macos

    if (!grid)
        return;

    const auto &cells = grid->getCells();
    for (int y = 0; y < grid->getHeight(); y++)
    {
        for (int x = 0; x < grid->getWidth(); x++)
        {
            if (cells[y][x].getType() == TypeCell::Alive)
                std::cout << "1 ";
            else if (cells[y][x].getType() == TypeCell::Obstacle)
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
