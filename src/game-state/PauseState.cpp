#pragma once
#include "../../include/game-state/PlayState.hpp"
#include "../../include/game-state/GameState.hpp"
#include "../../include/game-state/PauseState.hpp"


// Override update to transition to PlayState
std::unique_ptr<GameState> PauseState::update() {
    // Logic for the PauseState update (if any)
    // Transition to PlayState
    return std::make_unique<PlayState>();  // Return a new PlayState instance
}
