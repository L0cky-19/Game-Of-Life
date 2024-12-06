#pragma once
#include <string>

#include "../Grid.hpp"
#include "../renderer/Observer.hpp"

using namespace std;

struct GridDimensions
{
    int width;
    int height;
};

class FileHandler : public Observer
{
public:
    GridDimensions loadDimensions(string filename);
    vector<vector<int>> loadInputFromFile(string filename);
    void saveGridToFile(Grid *grid);
    void update(Subject* subject) override;
    virtual ~FileHandler();
    /*
    Pattern loadPatternFromFile(string filename);
    void savePatternToFile(Pattern pattern, string filename);
    */
};
