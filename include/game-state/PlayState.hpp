#pragma once
#include "GameState.hpp"
#include "PauseState.hpp" // Include PauseState since we transition to it

// Derived class representing the Play state
class PlayState : public GameState {
public:
    // Override the update function to transition to PauseState
    std::unique_ptr<GameState> update() override;
};
