#pragma once
#include "GameState.hpp"

//TODO: inherit public or private?
class PauseState : public GameState {
    GameState override update();
}
