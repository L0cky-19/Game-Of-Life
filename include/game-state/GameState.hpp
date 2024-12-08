#pragma once
#include <memory>

class GameState {
public:
    virtual ~GameState() = default;
    virtual std::unique_ptr<GameState> update() = 0;
};
