#include "../../include/renderer/ConsoleRenderer.hpp"
#include <iostream>
using namespace std;
void ConsoleRenderer::update(Subject* subject) {
    render(nullptr);
}

void ConsoleRenderer::render(Grid* grid) {
    std::cout << "Console Rendering Grid" << std::endl;
}

string ConsoleRenderer::getName() const  {
    return "Console";
}
