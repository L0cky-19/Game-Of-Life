#include "../../include/game-state/PlayState.hpp"
#include "../../include/game-state/GameState.hpp"
#include "../../include/game-state/PauseState.hpp"

std::unique_ptr<GameState> PauseState::update() {
    return std::make_unique<PlayState>();
}
