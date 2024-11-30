#pragma once
#include "../../include/game-state/PlayState.hpp"
#include "../../include/game-state/GameState.hpp"
#include "../../include/game-state/PauseState.hpp"
GameState PauseState::update() {
    return new PlayState();
}
