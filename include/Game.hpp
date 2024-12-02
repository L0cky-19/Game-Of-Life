#ifndef GAME
#define GAME

#include <string>

#include "Grid.hpp"
#include "IRenderer.hpp"
#include "GameState.hpp"
#include "IEvolutionStrategy.hpp"

class Game
{
protected:
    Grid grid;
    IRenderer *renderer;
    GameState *currentState;
    IEvolutionStrategy *evolutionStrategy;
    float iteration Delay;

public:
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