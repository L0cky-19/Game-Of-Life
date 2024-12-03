#include "../../include/renderer/ConsoleRenderer.hpp"
#include <iostream>

void ConsoleRenderer::update(Subject* subject) {
    render(nullptr);
}

void ConsoleRenderer::render(Grid* grid) {
    std::cout << "Console Rendering Grid" << std::endl;
}

