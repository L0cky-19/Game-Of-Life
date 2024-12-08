#include "../../include/input/Config.hpp"
#include "../../include/Game.hpp"
#include "../../include/input/InputHandler.hpp"
#include "../../include/evolution-strategy/HighLifeEvolution.hpp"
#include "../../include/evolution-strategy/ClassicEvolution.hpp"
#include "../../include/renderer/GraphicRenderer.hpp"
#include "../../include/renderer/ConsoleRenderer.hpp"

Config::Config() :
    questions{
        {inputType::inputLoadChoice, "\033[31mDo you want to load from file?\033[0m (y/n): "},
        {inputType::inputFilename, "\033[31mEnter the name of the saved game file or select a pattern: (0: dying, 1: glider-gun, 2: glider, 3: oscillator, 4: spaceship , 5: stable)\033[0m "},
        {inputType::inputGridDataWidth, "\033[31mEnter grid width:\033[0m "},
        {inputType::inputGridDataHeight, "\033[31mEnter grid height:\033[0m "},
        {inputType::inputGridToroidal, "\033[31mDo you want a toroidal grid?\033[0m (y/n): "},
        {inputType::inputEvolutionStrategy, "\033[31mSelect evolution strategy:\033[0m (0 for basic, 1 for highlife): "},
        {inputType::inputRenderer, "\033[31mSelect renderer\033[0m (0 for console, 1 for graphical interface): "},
        {inputType::inputIterationNumber, "\033[31mEnter number of iterations:\033[0m "},
        {inputType::inputIterationDelay, "\033[31mEnter delay between iterations:\033[0m (ms) "}
    },
    validResponses{
        {inputType::inputLoadChoice, {"y", "n"}},
        {inputType::inputFilename, {"0", "1", "2", "3", "4", "5"}},
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
    system("cls");
    cout << "\033[32mWelcome to Conway's Game of Life! \n\033[0m\n";
    cout << "========================================================\n";

    string loadChoice = inputLoadChoice();
    FileHandler *filehandler = new FileHandler();

    Grid* grid;
    if (loadChoice == "y") {
        bool validFile = false;
        string filename;
        while (!validFile) {
            try {
                filename = inputFilename();
                if (filename=="0"){
                    filename = "assets/patterns/dying.txt";
                } else if (filename=="1"){
                    filename = "assets/patterns/glider-gun.txt";
                } else if (filename=="2"){
                    filename = "assets/patterns/glider.txt";
                } else if (filename=="3"){
                    filename = "assets/patterns/oscillator.txt";
                } else if (filename=="4"){
                    filename = "assets/patterns/spaceship.txt";
                } else if (filename=="5"){
                    filename = "assets/patterns/stable.txt";
                }
                GridDimensions dims = filehandler->loadDimensions(filename);
                vector<vector<int>> fetchedCells = filehandler->loadInputFromFile(filename);
                grid = new Grid(dims.width, dims.height);
                grid->initCells(fetchedCells);
                validFile = true;
            } catch (const runtime_error& e) {
                cout << "\033[31mErreur : " << e.what() << "\033[0m\n";
            }
        }
    } else {
        GridData gridData = inputGridData();
        grid = new Grid(gridData.width, gridData.height);
        grid->initCellsRandom();
    }

    bool toroidal = inputGridToroidal();
    grid->setIsToroidal(toroidal);
    game->setGrid(grid);

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
