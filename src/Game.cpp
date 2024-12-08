#include <iostream>
#include <limits>
#include <chrono>
#include <thread>
#include <typeinfo>
#include "../include/Game.hpp"
#include "../include/game-state/GameState.hpp"
#include "../include/game-state/PauseState.hpp"
#include "../include/game-state/PlayState.hpp"
#include "../include/evolution-strategy/HighLifeEvolution.hpp"
#include "../include/evolution-strategy/ClassicEvolution.hpp"
#include "../include/renderer/ConsoleRenderer.hpp"
#include "../include/renderer/GraphicRenderer.hpp"
#include "../include/input/Config.hpp"
using namespace std;

// TODO: stoi au lieu de static cast?
void Game::setup() {
    config.setup(this);
}

void Game::displaySettings(string filename, Grid *grid) {
    cout << "\n=== Settings Summary ===\n";
    cout << "Grid Width: " << grid->getWidth() << "\n";
    cout << "Grid Height: " << grid->getHeight() << "\n";
    cout << "Is Toroidal: " << (grid->getIsToroidal() ? "Yes" : "No") << "\n";
    cout << "Evolution Strategy: " << this->getEvolutionStrategy()->getName() << "\n";
    cout << "Renderer: " << this->getRenderer()->getName() << "\n";
    cout << "Iteration Delay: " << this->getIterationDelay() << " ms\n";
    cout << "Playing from saved game: " << (filename.empty() ? "No" : "Yes") << "\n";
    if (!filename.empty())
    {
        cout << "Saved Game File: " << filename << "\n";
    }
    cout << "Fetched grid: ";
    grid->printCells();
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
            std::cout << "Fin du jeu - Grille stable" << std::endl;
            break;
        }
        if (iterationCounter > maxIterations)
        {
            gameIsRunning = false;
            std::cout << "Fin du jeu - Nombre maximum d'itérations atteint" << std::endl;
            break;
        }

        this->notify(); // notification des observers (renderer & filehandler)
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int64_t>(this->getIterationDelay())));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(5000)));
    cout << "\n"
         << "Fin de la partie" << endl;
}

void Game::pause() // TODO: pas logique d'avoir ces deux fonctions qui font la meme chose.
{
    currentState->update();
}

void Game::resume()
{
    currentState->update();
}

void Game::setRenderer(IRenderer *renderer) {
    this->renderer = renderer;
}

void Game::setState(GameState *state) {
    this->currentState = state;
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
    currentState(nullptr),
    evolutionStrategy(nullptr),
    fileHandler(nullptr),
    iterationDelay(0),
    numberOfIterations(0),
    isPaused(false),
    isGameOver(false)
{}

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

FileHandler *Game::getFileHandler() const {
    return this->fileHandler;
}

void Game::setFileHandler(FileHandler *filehandler) {
    this->fileHandler = filehandler;
}
