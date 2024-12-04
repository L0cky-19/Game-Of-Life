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

//TODO: nombre d'iterations?
//TODO: class config pour simplifier Game? ( game aurait un objet config et config aurait toutes les methodes de config )
//TODO: stoi au lieu de static cast?
//TODO: subscriptions? (renderer & filehandler sub a update de la grille?)
//TODO: init grille et tout dans setup?
//TODO: for pause use multithreading??? a second thread for the console cin so that if the user gives a pause input. We use an IPC (inter processing ...) and it tells the other thread to stop.
//TODO: make file handler a subject
void Game::setup()
{
    cout << "=== Evolution Simulation Settings ===\n";

    string filename = this->inputLoadChoice();
    GridData gridData = this->inputGridData(); //FIXME: demander que la grid data quand filename.empty()
    this->inputRenderer();
    this->inputEvolutionStrategy();
    this->inputIterationDelay();


    FileHandler* filehandler = new FileHandler();
    this->setFileHandler(filehandler); // needed ?

    Grid grid = Grid(gridData.width, gridData.height, gridData.isToroidal);
    if (filename.empty()) {
        grid.initCellsRandom();
    } else {
        vector<vector<int>> fetchedCells = filehandler->loadInputFromFile(filename);
        grid.initCells(fetchedCells);
    }
    this->setGrid(&grid);

    this->displaySettings(filename, grid);
    grid.printCells();
    // todo: subscribe / attach
    //this->getGrid()->attach(this->getRenderer());
    //this->getGrid()->attach(this->getFileHandler());
}

void Game::displaySettings(string filename, Grid grid)
{
    cout << "\n=== Settings Summary ===\n";
    cout << "Grid Width: " << grid.getWidth() << "\n";
    cout << "Grid Height: " << grid.getHeight() << "\n";
    cout << "Is Toroidal: " << (grid.getIsToroidal() ? "Yes" : "No") << "\n";
    cout << "Evolution Strategy: " << this->getEvolutionStrategy()->getName() << "\n";
    cout << "Renderer: " << this->getRenderer()->getName() << "\n";
    cout << "Iteration Delay: " << this->getIterationDelay() << " ms\n";
    cout << "Playing from saved game: " << (filename.empty() ? "No" : "Yes") << "\n";
    if (!filename.empty()) {
        cout << "Saved Game File: " << filename << "\n";
    }
    cout << "Fetched grid: ";
    grid.printCells();
}

void Game::run()
{
    bool gameIsRunning = true;
    int counter = 0;
    while (gameIsRunning) {
        counter++;
        cout << "counter" <<counter;
        grid->printCells();
        this->getRenderer()->render(this->getGrid());
        //grid->calculateNextGen(); //TODO: rename to nextIteration that encapsulates the other logic
        std::this_thread::sleep_for(std::chrono::milliseconds(/*TODO:static_cast<int>(this->getIterationDelay()))*/5000));
    }
}


void Game::pause() //TODO: pas logique d'avoir ces deux fonctions qui font la meme chose.
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

Game::Game() {} //TODO: needed or not?

string Game::inputLoadChoice() {
    char loadChoice;
    string filename;

    cout << "Do you want to load a saved game? (y/n): ";
    cin >> loadChoice;

    if (loadChoice == 'y' || loadChoice == 'Y') {
        do {
            cout << "Enter the name of the saved game file: ";
            cin >> filename;

            if (filename.empty()) {
                cout << "Invalid input. Please enter a valid filename.\n";
            }
        } while (filename.empty());
    }
    return filename.empty() ? "" : filename;
}

GridData Game::inputGridData() { //TODO: validation?
    GridData gridData;
    char toroidal;

    cout << "Enter grid width: ";
    cin >> gridData.width;

    cout << "Enter grid height: ";
    cin >> gridData.height;

    cout << "Is the grid toroidal? (y/n): ";
    cin >> toroidal;

    bool isToroidal = (isToroidal == 'y' || isToroidal == 'Y');
    gridData.isToroidal = isToroidal;

    return gridData;

}

void Game::inputEvolutionStrategy() {
    int evolutionStrategy = -1;
    while (true) {
        cout << "Select evolution strategy (0 for basic, 1 for highlife): ";
        cin >> evolutionStrategy;

        if (cin.fail() || (evolutionStrategy != 0 && evolutionStrategy != 1)) {
            cin.clear(); // Clear the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter 0 or 1.\n";
        } else {
            break;
        }
    }

    // todo: enum?
    if (evolutionStrategy == 0) {
        this->setEvolutionStrategy(new ClassicEvolution()); // Assuming ClassicEvolution is defined
    } else {
        this->setEvolutionStrategy(new HighLifeEvolution()); // Assuming HighLifeEvolution is defined
    }
}


void Game::inputRenderer() {
    int renderer = -1;
  while (true) {
        cout << "Select renderer (0 for console, 1 for graphical interface): ";
        cin >> renderer;

        if (cin.fail() || (renderer != 0 && renderer != 1)) {
            cin.clear(); // Clear the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter 0 or 1.\n";
        } else {
            break;
        }
    }
    //todo: enum ? SUBSCRIBE!!
    if (renderer == 0) {
        this->setRenderer(new ConsoleRenderer()); // Assuming ConsoleRenderer is defined
    } else {
        this->setRenderer(new GraphicRenderer()); // Assuming GraphicRenderer is defined
    }
}

void Game::inputIterationDelay() {

    int iterationDelay = -1;
while (true) {

        cout << "Enter iteration delay in milliseconds: ";
        cin >> iterationDelay;

        if (cin.fail() || iterationDelay < 0) {
            cin.clear(); // Clear the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a non-negative number.\n";
        } else {
            break;
        }
    }
    this->setIterationDelay(static_cast<float>(iterationDelay)); // Assuming iterationDelay is a float

}


IRenderer* Game::getRenderer() const {
    return renderer;
}

IEvolutionStrategy* Game::getEvolutionStrategy() const {
    return evolutionStrategy;
}

float Game::getIterationDelay() const { //TODO: int
    return this->iterationDelay;
}

void Game::setGrid(Grid *grid)
{
    this->grid = grid;
}

Grid Game::getGrid() const
{
    return grid;
}


FileHandler* Game::getFileHandler() const
{
    return this->fileHandler;
}

void Game::setFileHandler(FileHandler *filehandler) {
    this->fileHandler = filehandler;
}
