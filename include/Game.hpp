#pragma once
#include <string>

#include "./renderer/IRenderer.hpp"
#include "./evolution-strategy/IEvolutionStrategy.hpp"
#include "./file-handler/FileHandler.hpp"
#include "./game-state/GameState.hpp"

class Game
{
protected:
    Grid *grid;
    IRenderer *renderer;
    GameState *currentState;
    IEvolutionStrategy *evolutionStrategy;
    FileHandler *fileHandler;
    float iterationDelay;

public:
    bool isPaused;
    bool isGameOver;

    Game(/*std::string filename*/);

    void run();
    void setup();
    void pause();
    void resume();

    // setters
    void setRenderer(IRenderer *renderer);
    void setState(GameState *state);
    void setEvolutionStrategy(IEvolutionStrategy *strategy);
    void setIterationDelay(int iterationDelay);
};
