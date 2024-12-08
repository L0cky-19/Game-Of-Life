#include "../../include/renderer/IRenderer.hpp"
#include "../../include/Game.hpp"
#include <iostream>

void IRenderer::update(Subject *subject) {
    Game *game = dynamic_cast<Game*>(subject);
    if (game) {
        render(game->getGrid());
    } else {
        // Handle the case where the subject is not a Game
        std::cerr << "Error: Subject is not of type Game." << std::endl;
    }
}
