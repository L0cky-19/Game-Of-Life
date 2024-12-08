#pragma once
#include "IRenderer.hpp"
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class GraphicRenderer : public IRenderer {
private:
    sf::RenderWindow window;
    sf::Font font;
    std::vector<sf::Text> configTexts;
    sf::Text inputText;
    std::string currentInput;
    bool waitingForInput;
public:
    GraphicRenderer();
    void render(Grid* grid) override;
    void update(Subject* subject) override;
    sf::RenderWindow& getWindow() { return window; } //TODO: put in cpp
    string getName() const override;
    virtual ~GraphicRenderer() override {
        if (window.isOpen()) {
            window.close();
        }
    }

};
