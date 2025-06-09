#pragma once
#include <set>
#include "../Abstractions/Animal.h"
#include "World.h"

class MovementManager {
public:
    static void processMovements(World& world, std::set<Organism*>& toDie);
};
