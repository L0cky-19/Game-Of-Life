#include "../../include/renderer/GraphicRenderer.hpp"
#include "../../include/Grid.hpp"
#include <iostream>

GraphicRenderer::GraphicRenderer()
    : window(sf::VideoMode(800, 600), "Game of Life"), waitingForInput(false)
{
    window.setFramerateLimit(60);

    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        std::cout << "Erreur de chargement de la police" << std::endl;
    }

    inputText.setFont(font);
    inputText.setCharacterSize(20);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(50, 500);
}

void GraphicRenderer::update(Subject *subject)
{
    if (Grid *grid = dynamic_cast<Grid *>(subject))
    {
        render(grid);
    }
}

void GraphicRenderer::render(Grid *grid)
{
    if (!grid)
        return;                     // Protection against null pointers
    window.clear(sf::Color::White); // Clear the window

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close(); // Close the window if the close event is triggered
        }
    }

    const int cellSize = 20;
    const auto &cells = grid->getCells();
    for (int y = 0; y < grid->getHeight(); y++)
    {
        for (int x = 0; x < grid->getWidth(); x++)
        {
            sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
            cell.setPosition(x * cellSize, y * cellSize);

            if (cells[y][x].getType() == TypeCell::Alive)
                cell.setFillColor(sf::Color::Black);
            else if (cells[y][x].getType() == TypeCell::Obstacle)
                cell.setFillColor(sf::Color::Red);
            else
                cell.setFillColor(sf::Color::White);

            cell.setOutlineColor(sf::Color(128, 128, 128));
            cell.setOutlineThickness(1);
            window.draw(cell);
        }
    }
    window.display(); // Display the rendered frame
}

string GraphicRenderer::getName() const
{
    return "Graphic";
}
