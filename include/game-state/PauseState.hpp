#pragma once
#include "PlayState.hpp" // Include PlayState since we transition to it

// Derived class representing the Pause state
class PauseState : public GameState {
public:
    PauseState() = default;
    virtual ~PauseState() override = default;
    // Override the update function to transition to PlayState
    std::unique_ptr<GameState> update() override;
};
