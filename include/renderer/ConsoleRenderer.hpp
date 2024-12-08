#pragma once
#include "IRenderer.hpp"
#include <string>
using namespace std;

class ConsoleRenderer : public IRenderer {
public:
    ConsoleRenderer() = default;
    void render(Grid* grid) override;
    string getName() const override;
    virtual ~ConsoleRenderer() override = default;
};
