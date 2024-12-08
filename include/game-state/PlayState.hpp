#pragma once
#include "GameState.hpp"
#include "PauseState.hpp"

class PlayState : public GameState {
public:
    PlayState() = default;
    virtual ~PlayState() override = default;
    std::unique_ptr<GameState> update() override;
};
