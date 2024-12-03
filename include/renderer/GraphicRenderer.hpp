#pragma once
#include "IRenderer.hpp"
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class GraphicRenderer : public IRenderer {
private:
    sf::RenderWindow window;
public:
    GraphicRenderer();
    virtual ~GraphicRenderer() = default;
    void render(Grid* grid) override;
    void update(Subject* subject) override;
    sf::RenderWindow& getWindow() { return window; } //TODO: put in cpp

 string getName() const override;


};
