#pragma once
#include "../Cell.hpp"
#include <string>
//TODO: check if we respect strategy design pattern
//TODO: no implementation file needed right?
using namespace std;

class IEvolutionStrategy {
    public:
        virtual ~IEvolutionStrategy() = default;
        // true si vivante prochaine étape, false sinon
        virtual bool evolve(Cell* cell,int liveNeighbors) const = 0;
        virtual string getName() const = 0;
};
