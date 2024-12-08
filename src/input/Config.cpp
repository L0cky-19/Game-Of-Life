#include "../../include/input/Config.hpp"
#include "../../include/Game.hpp"
#include "../../include/input/InputHandler.hpp"
#include "../../include/evolution-strategy/HighLifeEvolution.hpp"
#include "../../include/evolution-strategy/ClassicEvolution.hpp"
#include "../../include/renderer/GraphicRenderer.hpp"
#include "../../include/renderer/ConsoleRenderer.hpp"

Config::Config() :
    questions{
        {inputType::inputLoadChoice, "Do you want to load from file? (y/n): "},
        {inputType::inputFilename, "Enter the name of the saved game file: "},
        {inputType::inputGridDataWidth, "Enter grid width: "},
        {inputType::inputGridDataHeight, "Enter grid height: "},
        {inputType::inputGridToroidal, "Do you want a toroidal grid? (y/n): "},
        {inputType::inputEvolutionStrategy, "Select evolution strategy (0 for basic, 1 for highlife): "},
        {inputType::inputRenderer, "Select renderer (0 for console, 1 for graphical interface): "},
        {inputType::inputIterationNumber, "Enter number of iterations: "},
        {inputType::inputIterationDelay, "Enter delay between iterations (ms): "}
    },
    validResponses{
        {inputType::inputLoadChoice, {"y", "n"}},
        {inputType::inputFilename, {}},
        {inputType::inputGridDataWidth, {}},
        {inputType::inputGridDataHeight, {}},
        {inputType::inputGridToroidal, {"y", "n"}},
        {inputType::inputEvolutionStrategy, {"0", "1"}},
        {inputType::inputRenderer, {"0", "1"}},
        {inputType::inputIterationNumber, {}},
        {inputType::inputIterationDelay, {}}
    },
    inputHandler(make_unique<InputHandler>()){}

void Config::setup(Game *game) {
    cout << "=== Evolution Simulation Settings ===\n";

    string loadChoice = inputLoadChoice();
    FileHandler *filehandler = new FileHandler();

    Grid* grid;
    if (loadChoice == "y") {
        string filename = inputFilename();
        GridDimensions dims = filehandler->loadDimensions(filename);
        vector<vector<int>> fetchedCells = filehandler->loadInputFromFile(filename);
        grid = new Grid(dims.width, dims.height, true);
        grid->initCells(fetchedCells);
    } else {
        GridData gridData = inputGridData();
        grid = new Grid(gridData.width, gridData.height, gridData.isToroidal);
        grid->initCellsRandom();
    }

    game->setGrid(grid);
    inputGridToroidal();

    // Configurer l'evolution strategy
    string strategyChoice = inputEvolutionStrategy();
    IEvolutionStrategy* strategy = (strategyChoice == "1")
        ? static_cast<IEvolutionStrategy*>(new HighLifeEvolution())
        : static_cast<IEvolutionStrategy*>(new ClassicEvolution());
    game->setEvolutionStrategy(strategy);

    game->setNumberOfIterations(this->inputIterationNumber());
    game->setIterationDelay(this->inputIterationDelay());

    // Configurer le renderer
    string rendererChoice = this->inputRenderer();
    IRenderer* renderer = (rendererChoice == "1")
        ? static_cast<IRenderer*>(new GraphicRenderer())
        : static_cast<IRenderer*>(new ConsoleRenderer());
    game->setRenderer(renderer);

    auto rendererPtr = std::shared_ptr<Observer>(renderer, [](Observer*){});
    auto fileHandlerPtr = std::shared_ptr<Observer>(filehandler, [](Observer*){});

    game->attach(rendererPtr);
    game->attach(fileHandlerPtr);

}

string Config::inputLoadChoice() {
    return inputHandler->handleInput<string>(
        questions.at(inputType::inputLoadChoice),
        "n",
        validResponses.at(inputType::inputLoadChoice),
        inputType::inputLoadChoice
    );
}

string Config::inputFilename() {
    return inputHandler->handleInput<string>(
        questions.at(inputType::inputFilename),
        "",
        validResponses.at(inputType::inputFilename),
        inputType::inputFilename
    );
}

GridData Config::inputGridData() {
    GridData data;
    data.width = inputHandler->handleInput<int>(
        questions.at(inputType::inputGridDataWidth),
        10,
        vector<int>{},
        inputType::inputGridDataWidth
    );

    data.height = inputHandler->handleInput<int>(
        questions.at(inputType::inputGridDataHeight),
        10,
        vector<int>{},
        inputType::inputGridDataHeight
    );
    return data;
}
bool Config::inputGridToroidal() {
    return inputHandler->handleInput<string>(
        questions.at(inputType::inputGridToroidal),
        "n",
        validResponses.at(inputType::inputGridToroidal),
        inputType::inputGridToroidal
    ) == "y";
}

string Config::inputEvolutionStrategy() {
    return inputHandler->handleInput<string>(
        questions.at(inputType::inputEvolutionStrategy),
        "0",
        validResponses.at(inputType::inputEvolutionStrategy),
        inputType::inputEvolutionStrategy
    );
}

string Config::inputRenderer() {
    return inputHandler->handleInput<string>(
        questions.at(inputType::inputRenderer),
        "0",
        validResponses.at(inputType::inputRenderer),
        inputType::inputRenderer
    );
}

int Config::inputIterationNumber() {
    return inputHandler->handleInput<int>(
        questions.at(inputType::inputIterationNumber),
        100,
        vector<int>{},
        inputType::inputIterationNumber
    );
}

int Config::inputIterationDelay() {
    return inputHandler->handleInput<int>(
        questions.at(inputType::inputIterationDelay),
        100,
        vector<int>{},
        inputType::inputIterationDelay
    );
}

Config::~Config() {}
