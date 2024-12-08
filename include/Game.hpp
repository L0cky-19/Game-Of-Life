#pragma once
#include <string>
#include <map>
#include <vector>

#include "./renderer/IRenderer.hpp"
#include "./evolution-strategy/IEvolutionStrategy.hpp"
#include "./file-handler/FileHandler.hpp"
#include "./game-state/GameState.hpp"
#include "./renderer/Subject.hpp"
#include "./input/Config.hpp"

class Game : public Subject
{
private:
    Config config;

protected: // TODO: why protected?
    Grid *grid;
    IRenderer *renderer;
    GameState *currentState;
    IEvolutionStrategy *evolutionStrategy;
    FileHandler *fileHandler; //TODO: besoin ici d'être attaché?
    int iterationDelay;
    int numberOfIterations;

public:
    bool isPaused;
    bool isGameOver;
    bool isFileLoaded = false;

    Game();

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
    string inputFilename();
    GridData inputGridData(); // returns width height and todoidal or not
    bool inputGridToroidal();
    void inputEvolutionStrategy();
    void inputRenderer();
    void inputIterationInfo();
    void displaySettings(string filename, Grid *grid); // todo: takes in the settings that are not attached to games, maybe ask a question to Alexis about this?

    // getters
    IRenderer *getRenderer() const;
    IEvolutionStrategy *getEvolutionStrategy() const;
    int getIterationDelay() const;
    Grid *getGrid() const;
    FileHandler *getFileHandler() const;
    int getNumberOfIterations() const;

    virtual ~Game() override {
        delete grid;
        delete renderer;
        delete currentState;
        delete evolutionStrategy;
        delete fileHandler;
    }
};
