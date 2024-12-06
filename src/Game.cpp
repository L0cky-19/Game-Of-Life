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

    string filename = this->inputLoadChoice();
    GridData gridData = this->inputGridData(); // FIXME: demander que la grid data quand filename.empty()
    this->inputEvolutionStrategy();
    this->inputIterationInfo();

    FileHandler *filehandler = new FileHandler();
    this->setFileHandler(filehandler); // needed ?

    Grid *grid = new Grid(gridData.width, gridData.height, gridData.isToroidal);
    if (filename.empty())
    {
        grid->initCellsRandom();
    }
    else
    {
        GridDimensions dims = filehandler->loadDimensions(filename);
        gridData.width = dims.width;
        gridData.height = dims.height;
        cout << "Loaded dimensions - Width: " << dims.width << " Height: " << dims.height << endl;

        vector<vector<int>> fetchedCells = filehandler->loadInputFromFile(filename);
        cout << "Loaded grid:" << endl;
        for (const auto &row : fetchedCells)
        {
            for (int cell : row)
            {
                cout << cell << " ";
            }
            cout << endl;
        }

        grid = new Grid(gridData.width, gridData.height, gridData.isToroidal);
        grid->initCells(fetchedCells);
    }
    this->setGrid(grid);

    // this->displaySettings(filename, grid);
    this->inputRenderer();
    // todo: subscribe / attach
    this->attach(shared_ptr<Observer>(this->getRenderer()));
    this->attach(shared_ptr<Observer>(this->getFileHandler())); // Updated line
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

Game::Game() {} // TODO: needed or not?

string Game::inputLoadChoice()
{
    string loadChoice;
    string filename;
    isFileLoaded = false; // Initialisation par défaut

    do
    {
        cout << "Do you want to load a saved game? (y/n): ";
        getline(cin, loadChoice);

        // Trim leading and trailing spaces
        loadChoice.erase(0, loadChoice.find_first_not_of(' ')); // Trim leading spaces
        loadChoice.erase(loadChoice.find_last_not_of(' ') + 1); // Trim trailing spaces

        if (loadChoice.empty())
        {
            cout << "Please enter a valid input (y/n).\n";
            continue;
        }

        if (loadChoice == "y" || loadChoice == "Y")
        {
            do
            {
                isFileLoaded = true; // On met à true seulement si l'utilisateur choisit de charger un fichier
                cout << "Enter the name of the saved game file: ";
                getline(cin, filename);

                // Trim leading and trailing spaces
                filename.erase(0, filename.find_first_not_of(' ')); // Trim leading spaces
                filename.erase(filename.find_last_not_of(' ') + 1); // Trim trailing spaces

                if (filename.empty())
                {
                    cout << "Please enter a valid filename.\n";
                }
            } while (filename.empty());
            break;
        }
        else if (loadChoice == "n" || loadChoice == "N")
        {
            filename = "";
            break;
        }
        else
        {
            cout << "Invalid input. Please enter y or n.\n";
        }
    } while (true);

    return filename;
}

GridData Game::inputGridData()
{
    GridData gridData;
    string toroidalInput;
    bool validInput = false;

    if (!isFileLoaded)
    {
        // Première boucle pour la largeur
        do
        {
            cout << "Enter grid width: ";
            string widthInput;
            getline(cin, widthInput);

            widthInput.erase(0, widthInput.find_first_not_of(" \t"));
            widthInput.erase(widthInput.find_last_not_of(" \t") + 1);

            // Vérifier que la chaîne ne contient que des chiffres
            bool isNumber = !widthInput.empty() &&
                            widthInput.find_first_not_of("0123456789") == string::npos;

            try
            {
                if (!isNumber)
                {
                    throw invalid_argument("Not a number");
                }
                gridData.width = stoi(widthInput);
                if (gridData.width < 0)
                {
                    cout << "Please enter a positive number.\n";
                }
                else
                {
                    validInput = true;
                }
            }
            catch (const exception &)
            {
                cout << "Please enter a valid number.\n";
            }
        } while (!validInput);
        // Réinitialiser validInput pour la hauteur
        validInput = false;

        // Deuxième boucle pour la hauteur
        do
        {
            cout << "Enter grid height: ";
            string heightInput;
            getline(cin, heightInput);

            heightInput.erase(0, heightInput.find_first_not_of(" \t"));
            heightInput.erase(heightInput.find_last_not_of(" \t") + 1);

            // Vérifier que la chaîne ne contient que des chiffres
            bool isNumber = !heightInput.empty() && heightInput.find_first_not_of("0123456789") == string::npos;

            try
            {
                if (!isNumber)
                {
                    throw invalid_argument("Not a number");
                }
                gridData.height = stoi(heightInput);
                if (gridData.height < 0)
                {
                    cout << "Please enter a positive number.\n";
                }
                else
                {
                    validInput = true;
                }
            }
            catch (const exception &)
            {
                cout << "Please enter a valid number.\n";
            }
        } while (!validInput);
    }
    else
    {
        gridData.width = 0;
        gridData.height = 0;
    }

    validInput = false;

    do
    {
        cout << "Is the grid toroidal? (y/n): ";
        getline(cin, toroidalInput);

        // Trim leading and trailing spaces
        toroidalInput.erase(0, toroidalInput.find_first_not_of(' ')); // Trim leading spaces
        toroidalInput.erase(toroidalInput.find_last_not_of(' ') + 1); // Trim trailing spaces

        if (toroidalInput.empty())
        {
            cout << "Please enter a valid input.\n";
        }
        else if (toroidalInput == "y" || toroidalInput == "Y")
        {
            gridData.isToroidal = true;
            validInput = true;
        }
        else if (toroidalInput == "n" || toroidalInput == "N")
        {
            gridData.isToroidal = false;
            validInput = true;
        }
        else
        {
            cout << "Invalid input. Please enter y or n.\n";
        }
    } while (!validInput);

    return gridData;
}

void Game::inputEvolutionStrategy()
{
    bool validInput = false;
    int evolutionStrategy = 0; // Déclarer en dehors du try
    do
    {
        cout << "Select evolution strategy (0 for basic, 1 for highlife): ";
        string evolutionStrategyInput;
        getline(cin, evolutionStrategyInput);

        evolutionStrategyInput.erase(0, evolutionStrategyInput.find_first_not_of(" \t"));
        evolutionStrategyInput.erase(evolutionStrategyInput.find_last_not_of(" \t") + 1);

        // Vérifier que la chaîne ne contient que des chiffres
        bool isNumber = !evolutionStrategyInput.empty() &&
                        evolutionStrategyInput.find_first_not_of("0123456789") == string::npos;

        try
        {
            if (!isNumber)
            {
                throw invalid_argument("Not a number");
            }
            evolutionStrategy = stoi(evolutionStrategyInput);
            if (evolutionStrategy < 0 || evolutionStrategy > 1)
            {
                cout << "Please enter a valid number.\n";
            }
            else
            {
                validInput = true;
            }
        }
        catch (const exception &)
        {
            cout << "Please enter a valid number.\n";
        }
    } while (!validInput);

    if (evolutionStrategy == 0)
    {
        this->setEvolutionStrategy(new ClassicEvolution());
    }
    else
    {
        this->setEvolutionStrategy(new HighLifeEvolution());
    }
}

void Game::inputRenderer()
{
    bool validInput = false;
    int rendererChoice = 0; // Déclarer en dehors du try
    do
    {
        cout << "Select renderer (0 for console, 1 for graphical interface): ";
        string rendererInput;
        getline(cin, rendererInput);

        rendererInput.erase(0, rendererInput.find_first_not_of(" \t"));
        rendererInput.erase(rendererInput.find_last_not_of(" \t") + 1);

        // Vérifier que la chaîne ne contient que des chiffres
        bool isNumber = !rendererInput.empty() &&
                        rendererInput.find_first_not_of("0123456789") == string::npos;

        try
        {
            if (!isNumber)
            {
                throw invalid_argument("Not a number");
            }
            rendererChoice = stoi(rendererInput);
            if (rendererChoice < 0 || rendererChoice > 1)
            {
                cout << "Please enter a valid number.\n";
            }
            else
            {
                validInput = true;
            }
        }
        catch (const exception &)
        {
            cout << "Please enter a valid number.\n";
        }
    } while (!validInput);

    if (rendererChoice == 0)
    {
        this->setRenderer(new ConsoleRenderer());
    }
    else
    {
        this->setRenderer(new GraphicRenderer());
    }
}

void Game::inputIterationInfo()
{
    bool validInput = false;
    int iterationDelay = 0;
    do
    {
        cout << "Select iteration delay in milliseconds: ";
        string iterationDelayInput;
        getline(cin, iterationDelayInput);

        iterationDelayInput.erase(0, iterationDelayInput.find_first_not_of(" \t"));
        iterationDelayInput.erase(iterationDelayInput.find_last_not_of(" \t") + 1);

        bool isNumber = !iterationDelayInput.empty() &&
                        iterationDelayInput.find_first_not_of("0123456789") == string::npos;

        try
        {
            if (!isNumber)
            {
                throw invalid_argument("Not a number");
            }
            iterationDelay = stoi(iterationDelayInput);
            if (iterationDelay < 0)
            {
                cout << "Please enter a valid number.\n";
            }
            else
            {
                validInput = true;
            }
        }
        catch (const exception &)
        {
            cout << "Please enter a valid number.\n";
        }
    } while (!validInput);

    validInput = false;
    int numberOfIterations = 0;
    do
    {
        cout << "Select number of iterations: ";
        string numberOfIterationsInput;
        getline(cin, numberOfIterationsInput);

        numberOfIterationsInput.erase(0, numberOfIterationsInput.find_first_not_of(" \t"));
        numberOfIterationsInput.erase(numberOfIterationsInput.find_last_not_of(" \t") + 1);

        bool isNumber = !numberOfIterationsInput.empty() &&
                        numberOfIterationsInput.find_first_not_of("0123456789") == string::npos;

        try
        {
            if (!isNumber)
            {
                throw invalid_argument("Not a number");
            }
            numberOfIterations = stoi(numberOfIterationsInput);
            if (numberOfIterations < 1)
            {
                cout << "Please enter a valid number.\n";
            }
            else
            {
                validInput = true;
            }
        }
        catch (const exception &)
        {
            cout << "Please enter a valid number.\n";
        }
    } while (!validInput);

    this->setNumberOfIterations(numberOfIterations);
    std::cout << "Number of iterations: " << numberOfIterations << std::endl;
    this->setIterationDelay(static_cast<float>(iterationDelay));
    std::cout << "Iteration delay: " << iterationDelay << std::endl;
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
