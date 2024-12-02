#include "../include/renderer/ConsoleRenderer.hpp"
#include "../include/renderer/GraphicRenderer.hpp"
#include "../tests/renderer/mocks/MockGrid.hpp"

int main() {
    testing::MockGrid mockGrid;
    GraphicRenderer graphicRenderer;
    
    // Attacher le renderer à la grille mock
    mockGrid.attach(&graphicRenderer);
    
    // Boucle principale
    bool running = true;
    while (running) {
        // Gérer les événements SFML
        sf::Event event;
        while (graphicRenderer.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            }
        }
        
        // Simuler un changement dans la grille
        mockGrid.notify();
    }
    
    return 0;
}
