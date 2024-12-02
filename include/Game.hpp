#ifndef GAME
#define GAME

#include <string>

#include "src/Grid.hpp"
#include "src/IRenderer.hpp"
#include "src/GameState.hpp"
#include "IEvolutionStrategy.hpp"

class Game
{
protected:
    Grid *grid;
    IRenderer *renderer;
    GameState *currentState;
    IEvolutionStrategy *evolutionStrategy;
    FileHandler *fileHandler;

    float iteration Delay;

public:
    bool isPaused;
    bool isGameOver;

    Game(std::string filename);

    void run();
    void setup();
    void pause();
    void resume();
    void setRenderer(IRenderer *renderer);
    void setState(GameState *state);
    void setEvolutionStrategy(IEvolutionStrategy *strategy);
};

#endif