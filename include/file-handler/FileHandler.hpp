#pragma once
#include <string>

#include "../Grid.hpp"

using namespace std;

class FileHandler
{
public:
    Grid loadGridFromFile(string filename);
    void saveGridToFile(Grid grid);

    /*
    Pattern loadPatternFromFile(string filename);
    void savePatternToFile(Pattern pattern, string filename);
    */
};
