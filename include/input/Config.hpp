#pragma once
#include <map>
#include <string>
#include <vector>
#include "InputType.hpp"
#include "InputHandler.hpp"
#include <memory>
using namespace std;

class Game;

struct GridData {
    int height;
    int width;
    bool isToroidal;
};

class Config {
private:
    map<inputType, string> questions;
    map<inputType, vector<string>> validResponses;
    unique_ptr<InputHandler> inputHandler;
public:
    Config();
    void setup(Game *game);
    template<typename T>
    T getInput(inputType type, const T& defaultValue) {
        return inputHandler->handleInput(
            questions.at(type),
            defaultValue,
            validResponses.at(type),
            type
        );
    }
    string inputLoadChoice();
    string inputFilename();
    GridData inputGridData();
    bool inputGridToroidal();
    string inputEvolutionStrategy();
    string inputRenderer();
    int inputIterationNumber();
    int inputIterationDelay();
};
