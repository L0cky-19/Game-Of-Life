#include <iostream>

#include "include/Game.hpp"
#include "include/game-state/PauseState.hpp"

using namespace std;

void Game::run()
{
    while (!isGameOver())
    {
        grid->calculateNextGen();
        renderer->update();
        fileHandler->saveGridToFile();

        if (isPaused)
        {
            waitForResume(); // ? wait for user resumning the game
        }
    }
}

void Game::setup()
{
    UserConfig config = getUserInput();

    grid = new Grid(config.size);

    if (config.loadFromFile)
    {
        vector<bool> cells = fileHandler->loadGridFromFile(config.filename);
        grid->initializeFromVector(cells);
    }
    else
    {
        grid->initializeRandom(); // ? should change that
    }

    grid->subscribe(this);
}

void Game::pause()
{
    currentState->update();
}

void Game::resume()
{
    currentState->update();
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