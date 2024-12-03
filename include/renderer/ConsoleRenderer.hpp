#pragma once
#include "IRenderer.hpp"

class ConsoleRenderer : public IRenderer {
public:
    void render(Grid* grid) override;
    void update(Subject* subject) override;
};
