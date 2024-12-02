#include "../../include/renderer/GraphicRenderer.hpp"
#include "../../tests/renderer/mocks/MockGrid.hpp"

GraphicRenderer::GraphicRenderer() 
    : window(sf::VideoMode(800, 600), "Game of Life") {
    window.setFramerateLimit(60);
}

void GraphicRenderer::update(Subject* subject) {
    if (Grid* grid = dynamic_cast<Grid*>(subject)) {
        render(grid);
    }
}

void GraphicRenderer::render(Grid* grid) {
    window.clear(sf::Color::White);

    if (grid) {
        const int cellSize = 20;
        
        // Dessiner juste la grille pour l'instant
        for (int x = 0; x <= grid->getWidth(); x++) {
            sf::RectangleShape line(sf::Vector2f(1, cellSize * grid->getHeight()));
            line.setPosition(x * cellSize, 0);
            line.setFillColor(sf::Color::Black);
            window.draw(line);
        }

        for (int y = 0; y <= grid->getHeight(); y++) {
            sf::RectangleShape line(sf::Vector2f(cellSize * grid->getWidth(), 1));
            line.setPosition(0, y * cellSize);
            line.setFillColor(sf::Color::Black);
            window.draw(line);
        }
    }

    window.display();
}


