#pragma once
#include "PlayState.hpp"

class PauseState : public GameState {
public:
    PauseState() = default;
    virtual ~PauseState() override = default;
    std::unique_ptr<GameState> update() override;
};
