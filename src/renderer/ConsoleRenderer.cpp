#include "../../include/renderer/ConsoleRenderer.hpp"
#include <iostream>
using namespace std;
void ConsoleRenderer::update(Subject* subject) {
    render(nullptr);
}

void ConsoleRenderer::render(Grid* grid) {
    if (!grid) return;

    cout << "grid info";
    //grid->printCells();
    // Afficher la grille
    /*
    const auto& cells = grid->getCells();
    for (int y = 0; y < grid->getHeight(); y++) {
        for (int x = 0; x < grid->getWidth(); x++) {
            if (cells[y][x].getType() == TypeCell::Alive) {
                std::cout << "1 ";  // Cellule vivante
            } else {
                std::cout << "0 ";  // Cellule morte
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    */
}

string ConsoleRenderer::getName() const  {
    return "Console";
}
