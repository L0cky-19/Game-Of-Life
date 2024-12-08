#pragma once
#include "Observer.hpp"
#include "../Grid.hpp"
#include <string>

class IRenderer : public Observer {
public:
    virtual void render(Grid* grid) = 0;
    virtual string getName() const = 0;
    virtual ~IRenderer() = default;
};
