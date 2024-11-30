#pragma once
#include "GameState.hpp"

//TODO: inherit public or private?
class PlayState: public GameState {
    GameState override update();
}
