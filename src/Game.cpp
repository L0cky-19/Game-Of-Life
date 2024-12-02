#include <iostream>
#include "include/Game.hpp"

void Game::run()
{
    std::cout << "Running the Game of Life!" << std::endl;
}
void Game::setup()
{
    std::cout << "Setting up the game with the given filename." << std::endl;
}
void Game::pause()
{
    std::cout << "Pausing the game." << std::endl;
}
void Game::resume()
{
    std::cout << "Resuming the game." << std::endl;
}
void Game::setRenderer(IRenderer *renderer)
{
    this->renderer = renderer;
}
void Game::setState(GameState *state)
{
    this->currentState = state;
}
void Game::setEvolutionStrategy(IEvolutionStrategy *strategy)
{
    this->evolutionStrategy = strategy;
}