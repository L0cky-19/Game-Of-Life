#pragma once
#include "Observer.hpp"
#include "../Grid.hpp"
#include <string>

class IRenderer : public Observer {
public:
    virtual ~IRenderer() = default;
    virtual void render(Grid* grid) = 0;
    virtual string getName() const = 0;
};
