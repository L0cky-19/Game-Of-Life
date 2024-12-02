#ifndef IRENDERER_HPP
#define IRENDERER_HPP

#include "Observer.hpp"
#include "../../tests/renderer/mocks/MockGrid.hpp"

class IRenderer : public Observer {
public:
    virtual ~IRenderer() = default;
    virtual void render(Grid* grid) = 0;
};

#endif // IRENDERER_HPP
    