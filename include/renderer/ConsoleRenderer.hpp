#pragma once
#include "IRenderer.hpp"
#include <string>
using namespace std;

class ConsoleRenderer : public IRenderer {
public:
    ConsoleRenderer() = default;
    virtual ~ConsoleRenderer() override = default;
    void render(Grid* grid) override;
    void update(Subject* subject) override;
    string getName() const override;
};
