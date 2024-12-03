#pragma once
#include "Observer.hpp"
#include "../Grid.hpp"
class IRenderer : public Observer {
public:
    virtual ~IRenderer() = default;
    virtual void render(Grid* grid) = 0;
};
