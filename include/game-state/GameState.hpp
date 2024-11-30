#pragma once
#include "Game.hpp"
// on créé un gamestate pour faire en sorte que ca soit plus simple d'implémenter des changements qui arrivent quand le user play ou pause (avec des observers par exemple)
//TODO: rename to IGameState? check proper naming
class GameState {
    private:
        Game* game;
    public:
        void virtual update() {} = 0;
};
