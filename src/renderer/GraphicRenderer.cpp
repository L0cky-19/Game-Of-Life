#include "../../include/renderer/GraphicRenderer.hpp"
#include "../../include/Grid.hpp"
#include "../../include/Game.hpp"
#include <iostream>

GraphicRenderer::GraphicRenderer() : window(sf::VideoMode(800, 600), "Game of Life",sf::Style::Titlebar | sf::Style::Close), waitingForInput(false) {
    window.setFramerateLimit(60);

    // Chargement et définition de l'icône
    sf::Image icon;
    if (icon.loadFromFile("assets/icon.png")) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        std::cout << "Erreur de chargement de la police" << std::endl;
    }

    inputText.setFont(font);
    inputText.setCharacterSize(20);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(50, 500);
}

void GraphicRenderer::render(Grid *grid) {
    if (!grid)
        return;                     // Protection against null pointers
    window.clear(sf::Color::Black); // Clear the window

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close(); // Close the window if the close event is triggered
        }
    }


    // Calculate the maximum cell size to fit the grid within the window, considering padding
    const int maxCellSizeX = (window.getSize().x) / grid->getWidth();
    const int maxCellSizeY = (window.getSize().y) / grid->getHeight();
    const int cellSize = std::min(maxCellSizeX, maxCellSizeY); // Use the smaller size to ensure it fits

    const auto &cells = grid->getCells();
    // Calculate the starting position to center the grid with padding
    int startX = (window.getSize().x - (grid->getWidth() * cellSize)) / 2;
    int startY = (window.getSize().y - (grid->getHeight() * cellSize)) / 2;

    for (int y = 0; y < grid->getHeight(); y++)
    {
        for (int x = 0; x < grid->getWidth(); x++)
        {
            sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
            cell.setPosition(startX + x * cellSize, startY + y * cellSize); // Adjusted position

            if (cells[y][x].getType() == CellType::Alive)
                cell.setFillColor(sf::Color::Cyan);
            else if (cells[y][x].getType() == CellType::Obstacle)
                cell.setFillColor(sf::Color::Red);
            else
                cell.setFillColor(sf::Color(128, 128, 128));

            cell.setOutlineColor(sf::Color::Black);
            cell.setOutlineThickness(1);
            window.draw(cell);
        }
    }
    window.display(); // Display the rendered frame
}

string GraphicRenderer::getName() const {
    return "Graphic";
}
sf::RenderWindow& GraphicRenderer::getWindow() {
    return window;
}
