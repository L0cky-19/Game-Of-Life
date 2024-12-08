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
    FileHandler() = default;
    virtual ~FileHandler() = default;
    GridDimensions loadDimensions(string filename);
    vector<vector<int>> loadInputFromFile(string filename);
    void saveGridToFile(Grid *grid);
    void update(Subject* subject) override;
    /*
    Pattern loadPatternFromFile(string filename);
    void savePatternToFile(Pattern pattern, string filename);
    */
};
