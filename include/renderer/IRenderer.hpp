#pragma once
#include "../observer-pattern/Observer.hpp"
#include "../Grid.hpp"
#include <string>

class IRenderer : public Observer {
public:
    virtual void render(Grid* grid) = 0;
    virtual string getName() const = 0;
    void update(Subject *subject); // methode helper pour éviter la duplication de code
    virtual ~IRenderer() = default;
};
