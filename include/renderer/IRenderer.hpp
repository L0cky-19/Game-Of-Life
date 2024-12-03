#pragma once
#include "Observer.hpp"
#include "../../tests/renderer/mocks/MockGrid.hpp"

class IRenderer : public Observer {
public:
    virtual ~IRenderer() = default;
    virtual void render(Grid* grid) = 0;
};