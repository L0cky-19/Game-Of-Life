#pragma once
#include <string>

#include "./renderer/IRenderer.hpp"
#include "./evolution-strategy/IEvolutionStrategy.hpp"
#include "./file-handler/FileHandler.hpp"
#include "./game-state/GameState.hpp"
#include "./renderer/Subject.hpp"

struct GridData // todo: voir si on le deplace dans grid peut être?
{
    int height;
    int width;
    bool isToroidal;
};

class Game : public Subject
{
protected: // TODO: why protected?
    Grid *grid;
    IRenderer *renderer;
    GameState *currentState;
    IEvolutionStrategy *evolutionStrategy;
    FileHandler *fileHandler; //TODO: besoin ici d'être attaché?
    float iterationDelay;
    int numberOfIterations;

public:
    bool isPaused;
    bool isGameOver;
    bool isFileLoaded = false;

    Game(/*std::string filename*/);

    void run();
    void setup();
    void pause();
    void resume(); // TODO: rm?

    // setters
    void setRenderer(IRenderer *renderer);
    void setState(GameState *state);
    void setEvolutionStrategy(IEvolutionStrategy *strategy);
    void setIterationDelay(int iterationDelay);
    void setGrid(Grid *grid);
    void setFileHandler(FileHandler *filehandler);
    void setNumberOfIterations(int iterations);

    // todo: maybe export these to a config class?
    string inputLoadChoice(); // returns -1 if new game & text if he loads
    GridData inputGridData(); // returns width height and todoidal or not
    void inputEvolutionStrategy();
    void inputRenderer();
    void inputIterationInfo();
    void displaySettings(string filename, Grid *grid); // todo: takes in the settings that are not attached to games, maybe ask a question to Alexis about this?

    // getters
    IRenderer *getRenderer() const;
    IEvolutionStrategy *getEvolutionStrategy() const;
    float getIterationDelay() const;
    Grid *getGrid() const;
    FileHandler *getFileHandler() const;
    int getNumberOfIterations() const;

    ~Game() {
        delete grid;
        delete renderer;
        delete currentState;
        delete evolutionStrategy;
        delete fileHandler;
    }
};
