#pragma once
#include "IRenderer.hpp"
#include <SFML/Graphics.hpp>

class GraphicRenderer : public IRenderer {
public:
    GraphicRenderer();
    virtual ~GraphicRenderer() = default;
    void render(Grid* grid) override;
    void update(Subject* subject) override;
    sf::RenderWindow& getWindow() { return window; }

private:
    sf::RenderWindow window;
};
