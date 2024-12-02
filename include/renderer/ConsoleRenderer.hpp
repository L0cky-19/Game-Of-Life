#ifndef CONSOLE_RENDERER_HPP
#define CONSOLE_RENDERER_HPP

#include "IRenderer.hpp"

class ConsoleRenderer : public IRenderer {
public:
    virtual ~ConsoleRenderer() = default;
    void update(Subject* subject) override;
    void render(Grid* grid) override;
};

#endif // CONSOLE_RENDERER_HPP
