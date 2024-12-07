#include <iostream>
#include <limits>
#include <chrono>
#include <thread>
#include <typeinfo>
#include "../include/Game.hpp"
#include "../include/game-state/GameState.hpp"
#include "../include/game-state/PauseState.hpp"
#include "../include/game-state/PlayState.hpp"
#include "../include/evolution-strategy/HighLifeEvolution.hpp"
#include "../include/evolution-strategy/ClassicEvolution.hpp"
#include "../include/renderer/ConsoleRenderer.hpp"
#include "../include/renderer/GraphicRenderer.hpp"
using namespace std;

// TODO: nombre d'iterations?
// TODO: class config pour simplifier Game? ( game aurait un objet config et config aurait toutes les methodes de config )
// TODO: stoi au lieu de static cast?
// TODO: subscriptions? (renderer & filehandler sub a update de la grille?)
// TODO: init grille et tout dans setup?
// TODO: for pause use multithreading??? a second thread for the console cin so that if the user gives a pause input. We use an IPC (inter processing ...) and it tells the other thread to stop.
// TODO: make file handler a subject
void Game::setup()
{
    cout << "=== Evolution Simulation Settings ===\n";

    string loadChoice = this->inputLoadChoice();
    FileHandler *filehandler = new FileHandler();
    this->setFileHandler(filehandler);
    
    Grid* grid;
    if (loadChoice == "y") {  // Si on veut charger un fichier
        string filename = this->inputFilename();  // Demande le nom du fichier
        GridDimensions dims = filehandler->loadDimensions(filename);
        vector<vector<int>> fetchedCells = filehandler->loadInputFromFile(filename);
        grid = new Grid(dims.width, dims.height, true);  // TODO: gérer isToroidal depuis le fichier
        grid->initCells(fetchedCells);
    } else {
        GridData gridData = this->inputGridData();
        grid = new Grid(gridData.width, gridData.height, gridData.isToroidal);
        grid->initCellsRandom();  // Initialisation aléatoire
    }
    
    this->setGrid(grid);
    this->inputEvolutionStrategy();
    this->inputIterationInfo();
    this->inputRenderer();

    auto rendererPtr = std::shared_ptr<Observer>(renderer, [](Observer*){});
    auto fileHandlerPtr = std::shared_ptr<Observer>(fileHandler, [](Observer*){});

    this->attach(rendererPtr);
    this->attach(fileHandlerPtr);
}

void Game::displaySettings(string filename, Grid *grid)
{
    cout << "\n=== Settings Summary ===\n";
    cout << "Grid Width: " << grid->getWidth() << "\n";
    cout << "Grid Height: " << grid->getHeight() << "\n";
    cout << "Is Toroidal: " << (grid->getIsToroidal() ? "Yes" : "No") << "\n";
    cout << "Evolution Strategy: " << this->getEvolutionStrategy()->getName() << "\n";
    cout << "Renderer: " << this->getRenderer()->getName() << "\n";
    cout << "Iteration Delay: " << this->getIterationDelay() << " ms\n";
    cout << "Playing from saved game: " << (filename.empty() ? "No" : "Yes") << "\n";
    if (!filename.empty())
    {
        cout << "Saved Game File: " << filename << "\n";
    }
    cout << "Fetched grid: ";
    grid->printCells();
}

// TODO: make this a template
template <typename T>
T Game::inputLogic(const string& question, const T& defaultValue, vector<T> validResponses, inputType inputType) {
    T response;
    bool validInput = false;

    do {
        cout << question;
        string input;
        getline(cin, input);

        // Trim l'input
        input.erase(0, input.find_first_not_of(' '));
        input.erase(input.find_last_not_of(' ') + 1);

        // Vérifier si l'input est vide ou ne contient que des espaces
        if (input.empty() || input.find_first_not_of(" \t") == string::npos) {
            cout << "Input cannot be empty. Please try again.\n";
            continue;  // Retourne au début de la boucle
        }

        try {
            // Validation spécifique selon le type d'input
            if constexpr (std::is_same_v<T, string>) {
                if (inputType == inputType::inputFilename) {
                    // Vérification que le fichier n'est pas que des espaces
                    if (input.find_first_not_of(" \t") == string::npos) {
                        throw runtime_error("Filename cannot be empty or only whitespace");
                    }
                    response = input;
                    validInput = true;
                }
                else {
                    // Pour les autres inputs string, vérifier si la réponse est valide
                    if (!validResponses.empty() && 
                        find(validResponses.begin(), validResponses.end(), input) == validResponses.end()) {
                        throw runtime_error("Invalid input. Please choose from the available options.");
                    }
                    response = input;
                    validInput = true;
                }
            }
            else if constexpr (std::is_same_v<T, int>) {
                // Vérifier que l'input ne contient que des chiffres
                if (input.find_first_not_of("0123456789") != string::npos) {
                    throw runtime_error("Please enter only numbers");
                }
                
                int value = std::stoi(input);
                
                // Validation spécifique selon le type d'input
                if (inputType == inputType::inputGridDataWidth) {
                    if (value < 1 || value > 1000000) {
                        throw runtime_error("Grid dimensions must be between 1 and 1000000");
                    }
                }
                else if (inputType == inputType::inputGridDataHeight) {
                    if (value < 1 || value > 1000000) {
                        throw runtime_error("Grid dimensions must be between 1 and 1000000");
                    }
                }
                else if (inputType == inputType::inputIterationNumber) {
                    if (value < 1 || value > 1000000) {
                        throw runtime_error("Value must be between 1 and 1000000");
                    }
                }
                else if (inputType == inputType::inputIterationDelay) {
                    if (value < 0 || value > 1000000) {
                        throw runtime_error("Value must be between 0 and 1000000");
                    }
                }
                
                response = value;
                validInput = true;
            }
            else if constexpr (std::is_same_v<T, bool>) {
                if (input != "y" && input != "n" && input != "Y" && input != "N") {
                    throw runtime_error("Please enter y or n");
                }
                response = (input == "y" || input == "Y");
                validInput = true;
            }
        }
        catch (const exception& e) {
            cout << e.what() << "\n";
        }
    } while (!validInput);

    return response;
}

// TODO: make this a template


void Game::run()
{
    bool gameIsRunning = true;
    int iterationCounter = 0;
    int maxIterations = this->getNumberOfIterations();
    // Grid* grid = this->getGrid();

    while (gameIsRunning)
    {
        iterationCounter++;
        if (grid->calculateNextGen(evolutionStrategy))
        {
            gameIsRunning = false;
            std::cout << "Fin du jeu - Grille stable" << std::endl;
            break;
        }
        if (iterationCounter > maxIterations)
        {
            gameIsRunning = false;
            std::cout << "Fin du jeu - Nombre maximum d'itérations atteint" << std::endl;
            break;
        }

        this->notify(); // notification des observers (renderer & filehandler)
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(this->getIterationDelay())));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(5000)));
    cout << "\n"
         << "Fin de la partie" << endl;
}

void Game::pause() // TODO: pas logique d'avoir ces deux fonctions qui font la meme chose.
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

Game::Game() : 
    questions{
        {inputType::inputLoadChoice, "Do you want to load from file? (y/n): "},
        {inputType::inputFilename, "Enter the name of the saved game file: "},
        {inputType::inputGridDataWidth, "Enter grid width: "},
        {inputType::inputGridDataHeight, "Enter grid height: "},
        {inputType::inputGridDataToroidal, "Do you want a toroidal grid? (y/n): "},
        {inputType::inputEvolutionStrategy, "Select evolution strategy (0 for basic, 1 for highlife): "},
        {inputType::inputIterationNumber, "Enter number of iterations: "},
        {inputType::inputIterationDelay, "Enter delay between iterations: "},
        {inputType::inputRenderer, "Select renderer (0 for console, 1 for graphical interface): "}
    },
    validResponses{
        {inputType::inputLoadChoice, {"y", "n"}},
        {inputType::inputFilename, {}},
        {inputType::inputGridDataWidth, {}},
        {inputType::inputGridDataHeight, {}},
        {inputType::inputGridDataToroidal, {"y", "n"}},
        {inputType::inputEvolutionStrategy, {"0", "1"}},
        {inputType::inputRenderer, {"0", "1"}},
        {inputType::inputIterationNumber, {}},
        {inputType::inputIterationDelay, {}}
    },
    grid(nullptr),
    renderer(nullptr),
    currentState(nullptr),
    evolutionStrategy(nullptr),
    fileHandler(nullptr),
    iterationDelay(0),
    numberOfIterations(0),
    isPaused(false),
    isGameOver(false)
{
    // Reste du constructeur si nécessaire
}
string Game::inputLoadChoice() {
    return inputLogic<string>(
        questions.at(inputType::inputLoadChoice),
        "n",
        validResponses.at(inputType::inputLoadChoice),
        inputType::inputLoadChoice
    );
}

string Game::inputFilename() {
    return inputLogic<string>(
        questions.at(inputType::inputFilename),
        "",
        validResponses.at(inputType::inputFilename),
        inputType::inputFilename
    );
}   

GridData Game::inputGridData() {
    GridData data;
    data.width = inputLogic<int>(
        questions.at(inputType::inputGridDataWidth),
        10,
        vector<int>{},
        inputType::inputGridDataWidth
    );
    
    data.height = inputLogic<int>(
        questions.at(inputType::inputGridDataHeight),
        10,
        vector<int>{},
        inputType::inputGridDataHeight
    );

    // Validation toroidal oui/non
    string toroidal = inputLogic<string>(
        questions.at(inputType::inputGridDataToroidal),
        "n",
        validResponses.at(inputType::inputGridDataToroidal),
        inputType::inputGridDataToroidal
    );
    data.isToroidal = (toroidal == "y");

    return data;
}

void Game::inputEvolutionStrategy() {
    string choice = inputLogic<string>(
        questions.at(inputType::inputEvolutionStrategy),
        "0",
        validResponses.at(inputType::inputEvolutionStrategy),
        inputType::inputEvolutionStrategy
    );
    
    if (choice == "0") {
        this->setEvolutionStrategy(new ClassicEvolution());
    } else {
        this->setEvolutionStrategy(new HighLifeEvolution());
    }
}

void Game::inputRenderer() {
    string choice = inputLogic<string>(
        questions.at(inputType::inputRenderer),
        "0",
        validResponses.at(inputType::inputRenderer),
        inputType::inputRenderer
    );
    
    if (choice == "0") {
        this->setRenderer(new ConsoleRenderer());
    } else {
        this->setRenderer(new GraphicRenderer());
    }
}

void Game::inputIterationInfo() {
    this->setNumberOfIterations(
        inputLogic<int>(
            questions.at(inputType::inputIterationNumber),
            100,
            vector<int>{},
            inputType::inputIterationNumber
        )
    );
    
    this->setIterationDelay(
        inputLogic<int>(
            questions.at(inputType::inputIterationDelay),
            100,
            vector<int>{},
            inputType::inputIterationDelay
        )
    );
}

void Game::setNumberOfIterations(int iterations)
{ // New setter method
    numberOfIterations = iterations;
}

IRenderer *Game::getRenderer() const
{
    return renderer;
}

IEvolutionStrategy *Game::getEvolutionStrategy() const
{
    return evolutionStrategy;
}

float Game::getIterationDelay() const
{ // TODO: int
    return this->iterationDelay;
}
int Game::getNumberOfIterations() const
{
    return this->numberOfIterations;
}
void Game::setGrid(Grid *grid)
{
    this->grid = grid;
}

Grid *Game::getGrid() const
{
    return grid;
}

FileHandler *Game::getFileHandler() const
{
    return this->fileHandler;
}

void Game::setFileHandler(FileHandler *filehandler)
{
    this->fileHandler = filehandler;
}
