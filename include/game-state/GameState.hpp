#pragma once
#include "../Game.hpp"
#include <memory> // For std::unique_ptr
// on créé un gamestate pour faire en sorte que ca soit plus simple d'implémenter des changements qui arrivent quand le user play ou pause (avec des observers par exemple)
//TODO: rename to IGameState? check proper naming
class GameState {
public:
    virtual ~GameState() = default;

    // Pure virtual function to update the game state
    virtual std::unique_ptr<GameState> update() = 0;
};
