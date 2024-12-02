#include "../include/renderer/ConsoleRenderer.hpp"
#include "../include/renderer/GraphicRenderer.hpp"
#include <iostream>

int main() {
    ConsoleRenderer consoleRenderer;
    GraphicRenderer graphicRenderer;
    
    // Boucle principale pour tester les renderers
    bool running = true;
    while (running) {
        // Test du ConsoleRenderer
        consoleRenderer.render(nullptr);
        
        // Test du GraphicRenderer
        graphicRenderer.render(nullptr);
        
        // Pour le GraphicRenderer, il faut gérer les événements SFML
        sf::Event event;
        while (graphicRenderer.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            }
        }
    }
    
    return 0;
}
