#pragma once
#include "Organism.h"
#include <vector>

class Death {
public:
    static void execute(Organism* organism, int currentTurn, class World* world);
};

