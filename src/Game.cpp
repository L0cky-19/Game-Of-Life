#include <iostream>

#include "../include/Game.hpp"
#include "../include/game-state/GameState.hpp"
#include "../include/game-state/PauseState.hpp"
#include "../include/game-state/PlayState.hpp"
#include "../include/evolution-strategy/HighLifeEvolution.hpp"
#include "../include/evolution-strategy/ClassicEvolution.hpp"
#include "../include/renderer/ConsoleRenderer.hpp"
#include "../include/renderer/GraphicRenderer.hpp"
#include <limits>

using namespace std;

/**
 * 1. Set current game state to play
 * 2. Set evolution strategy
 * 3. Set renderer
 * 4. Iteration delay
 * todo: nb of iterations
 */
void Game::setup()
{

    // todo maybe make this kind of class? UserConfig config = getUserInput();
    this->currentState = new PlayState();

    // ? user config
    int evolutionStrategy = -1;
    int renderer = -1;
    int iterationDelay = -1;

    cout << "=== Evolution Simulation Settings ===\n";

    // Input for evolution strategy
    while (true) {
        cout << "Select evolution strategy (0 for basic, 1 for highlife): ";
        cin >> evolutionStrategy;

        if (cin.fail() || (evolutionStrategy != 0 && evolutionStrategy != 1)) {
            cin.clear(); // Clear the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter 0 or 1.\n";
        } else {
            break;
        }
    }

    // Input for renderer
    while (true) {
        cout << "Select renderer (0 for console, 1 for graphical interface): ";
        cin >> renderer;

        if (cin.fail() || (renderer != 0 && renderer != 1)) {
            cin.clear(); // Clear the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter 0 or 1.\n";
        } else {
            break;
        }
    }

    // Input for iteration delay
    while (true) {
        cout << "Enter iteration delay in milliseconds: ";
        cin >> iterationDelay;

        if (cin.fail() || iterationDelay < 0) {
            cin.clear(); // Clear the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a non-negative number.\n";
        } else {
            break;
        }
    }

    // Display the gathered settings
    cout << "\n=== Settings Summary ===\n";
    cout << "Evolution Strategy: " << (evolutionStrategy == 0 ? "Basic" : "Highlife") << "\n";
    cout << "Renderer: " << (renderer == 0 ? "Console" : "Graphical Interface") << "\n";
    cout << "Iteration Delay: " << iterationDelay << " ms\n";

    // set the new values
    this->setIterationDelay(static_cast<float>(iterationDelay)); // Assuming iterationDelay is a float
    if (evolutionStrategy == 0) {
        this->setEvolutionStrategy(new ClassicEvolution()); // Assuming ClassicEvolution is defined
    } else {
        this->setEvolutionStrategy(new HighLifeEvolution()); // Assuming HighLifeEvolution is defined
    }

    if (renderer == 0) {
        this->setRenderer(new ConsoleRenderer()); // Assuming ConsoleRenderer is defined
    } else {
        this->setRenderer(new GraphicRenderer()); // Assuming GraphicRenderer is defined
    }


    /*
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

    grid->subscribe(this);*/
}
void Game::run()
{
    /*
    while (!isGameOver)
    {
        grid->calculateNextGen();
        renderer->update();
        fileHandler->saveGridToFile();

        if (isPaused)
        {
            waitForResume(); // ? wait for user resumning the game
        }
    }*/
}


void Game::pause() //TODO: pas logique d'avoir ces deux fonctions qui font la meme chose.
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

void Game::setIterationDelay(int iterationDelay)
{
    this->iterationDelay = iterationDelay;
}

Game::Game() {} //TODO: needed or not?
