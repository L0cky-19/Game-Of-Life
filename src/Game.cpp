#include <iostream>
#include <limits>
#include <chrono>
#include <thread>
#include <typeinfo>
#include "../include/Game.hpp"
#include "../include/evolution-strategy/HighLifeEvolution.hpp"
#include "../include/evolution-strategy/ClassicEvolution.hpp"
#include "../include/renderer/ConsoleRenderer.hpp"
#include "../include/renderer/GraphicRenderer.hpp"
#include "../include/input/Config.hpp"
using namespace std;

void Game::setup() {
    config.setup(this);
}

void Game::run()
{
    bool gameIsRunning = true;
    int iterationCounter = 0;
    int maxIterations = this->getNumberOfIterations();

    while (gameIsRunning)
    {
        iterationCounter++;
        if (grid->calculateNextGen(evolutionStrategy))
        {
            gameIsRunning = false;
            std::cout << "\n========================================================\n";
            std::cout << "\n\033[32mGame Over - Stable Grid\033[0m" << std::endl << std::endl;
            break;
        }
        if (iterationCounter > maxIterations)
        {
            gameIsRunning = false;
            std::cout << "\n========================================================\n";
            std::cout << "\n\033[32mGame Over - Maximum Number of Iterations Reached\033[0m" << std::endl << std::endl;
            break;
        }

        this->notify(); // notification des observers (renderer & filehandler)
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int64_t>(this->getIterationDelay())));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(3000)));
}



void Game::setRenderer(IRenderer *renderer) {
    this->renderer = renderer;
}

void Game::setEvolutionStrategy(IEvolutionStrategy *strategy) {
    this->evolutionStrategy = strategy;
}

void Game::setIterationDelay(int iterationDelay) {
    this->iterationDelay = iterationDelay;
}

Game::Game() :
    grid(nullptr),
    renderer(nullptr),
    evolutionStrategy(nullptr),
    iterationDelay(0),
    numberOfIterations(0) {}

void Game::setNumberOfIterations(int iterations) {
    numberOfIterations = iterations;
}

IRenderer *Game::getRenderer() const {
    return renderer;
}

IEvolutionStrategy *Game::getEvolutionStrategy() const {
    return evolutionStrategy;
}

int Game::getIterationDelay() const {
    return this->iterationDelay;
}
int Game::getNumberOfIterations() const {
    return this->numberOfIterations;
}
void Game::setGrid(Grid *grid) {
    this->grid = grid;
}

Grid *Game::getGrid() const {
    return grid;
}
