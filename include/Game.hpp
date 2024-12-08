#pragma once
#include <string>
#include <map>
#include <vector>
#include "./renderer/IRenderer.hpp"
#include "./evolution-strategy/IEvolutionStrategy.hpp"
#include "./file-handler/FileHandler.hpp"
#include "./observer-pattern/Subject.hpp"
#include "./input/Config.hpp"

class Game : public Subject {
private:
    Config config;
protected:
    Grid *grid;
    IRenderer *renderer;
    IEvolutionStrategy *evolutionStrategy;
    FileHandler *fileHandler; //TODO: besoin ici d'être attaché?
    int iterationDelay;
    int numberOfIterations;
public:
    Game();
    void run();
    void setup();

    // setters
    void setRenderer(IRenderer *renderer);
    void setEvolutionStrategy(IEvolutionStrategy *strategy);
    void setIterationDelay(int iterationDelay);
    void setGrid(Grid *grid);
    void setFileHandler(FileHandler *filehandler);
    void setNumberOfIterations(int iterations);

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
        delete evolutionStrategy;
        delete fileHandler;
    }
};
