#include "../../include/renderer/GraphicRenderer.hpp"

GraphicRenderer::GraphicRenderer() 
    : window(sf::VideoMode(800, 600), "Game of Life") {
    window.setFramerateLimit(60);
}

void GraphicRenderer::update(Subject* subject) {
    // Implémentation de base pour l'instant
    // Vous pourrez la modifier selon vos besoins
}

void GraphicRenderer::render(Grid* grid) {
    // Efface la fenêtre avec une couleur de fond
    window.clear(sf::Color::White);

    // Exemple : Dessiner une grille simple
    const int cellSize = 20;
    const int gridWidth = 30;
    const int gridHeight = 20;

    // Dessiner les lignes de la grille
    for (int x = 0; x <= gridWidth; x++) {
        sf::RectangleShape line(sf::Vector2f(1, cellSize * gridHeight));
        line.setPosition(x * cellSize, 0);
        line.setFillColor(sf::Color::Black);
        window.draw(line);
    }

    for (int y = 0; y <= gridHeight; y++) {
        sf::RectangleShape line(sf::Vector2f(cellSize * gridWidth, 1));
        line.setPosition(0, y * cellSize);
        line.setFillColor(sf::Color::Black);
        window.draw(line);
    }

    window.display();
}


