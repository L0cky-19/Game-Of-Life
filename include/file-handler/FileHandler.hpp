#pragma once
#include <string>
#include "../Grid.hpp"
#include "../renderer/Observer.hpp"
using namespace std;

struct GridDimensions {
    int width;
    int height;
};

class FileHandler : public Observer {
public:
    FileHandler() = default;
    GridDimensions loadDimensions(string filename);
    vector<vector<int>> loadInputFromFile(string filename); //TODO: check si l'implémentation est intelligente ou non
    void saveGridToFile(Grid *grid);
    void update(Subject* subject) override;
    virtual ~FileHandler() = default;
};
