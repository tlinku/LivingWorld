#pragma once
#include <set>
#include "../Abstractions/Animal.h"
#include "World.h"

class ReproductionManager {
public:
    static void processReproduction(World& world, std::set<Organism*>& toDie, std::vector<std::unique_ptr<Organism>>& toAdd);
};

