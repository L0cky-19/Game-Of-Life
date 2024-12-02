#ifndef GRAPHIC_RENDERER_HPP
#define GRAPHIC_RENDERER_HPP

#include "IRenderer.hpp"
#include <SFML/Graphics.hpp>

class GraphicRenderer : public IRenderer {
public:
    GraphicRenderer();
    virtual ~GraphicRenderer() = default;
    void update(Subject* subject) override;
    void render(Grid* grid) override;
    sf::RenderWindow& getWindow() { return window; }

private:
    sf::RenderWindow window;
};

#endif
