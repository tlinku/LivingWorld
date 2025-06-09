#pragma once
#include "Organism.h"

class World;

class Eating {
public:
    virtual bool canEat(Organism* other) = 0;
    virtual void eat(Organism* other, int currentTurn, World* world) = 0;
    virtual ~Eating() = default;
};
