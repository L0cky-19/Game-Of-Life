#pragma once
#include <string>
#include <vector>
#include "InputType.hpp"
using namespace std;

class InputHandler {
public:
    virtual ~InputHandler() = default;
    template <typename T>
    T handleInput(const string& question, const T& defaultValue, vector<T> validResponses, inputType inputType);
};

#include "InputHandler.tpp"
