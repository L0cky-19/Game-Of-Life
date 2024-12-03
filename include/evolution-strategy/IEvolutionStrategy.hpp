#pragma once
#include "../Cell.hpp"

//TODO: check if we respect strategy design pattern
//TODO: no implementation file needed right?
class IEvolutionStrategy {
    public:
        virtual ~IEvolutionStrategy() = default;
        // true si vivante prochaine étape, false sinon
        virtual bool evolve(Cell* cell,int liveNeighbors) const = 0;
};
