#pragma once
#include "../../include/game-state/PlayState.hpp"
#include "../../include/game-state/GameState.hpp"
#include "../../include/game-state/PauseState.hpp"

// Override update to transition to PauseState
std::unique_ptr<GameState> PlayState::update() {
    // Logic for the PlayState update (if any)
    // Transition to PauseState
    return std::make_unique<PauseState>();  // Return a new PauseState instance
}
