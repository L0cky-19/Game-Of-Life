#pragma once
#include <string>

#include "../Grid.hpp"

using namespace std;

struct GridDimensions
{
    int width;
    int height;
};

class FileHandler
{
public:
    GridDimensions loadDimensions(string filename);
    vector<vector<int>> loadInputFromFile(string filename);
    void saveGridToFile(Grid *grid);

    /*
    Pattern loadPatternFromFile(string filename);
    void savePatternToFile(Pattern pattern, string filename);
    */
};