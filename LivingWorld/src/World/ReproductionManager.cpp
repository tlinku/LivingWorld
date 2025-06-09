#include "ReproductionManager.h"
#include "../Organisms/Sheep.h"
#include "../Organisms/Wolf.h"
#include "../Organisms/Dandelion.h"
#include "../Organisms/Toadstool.h"
#include "../Abstractions/Plant.h"
#include <vector>
#include <set>

void ReproductionManager::processReproduction(World& world, std::set<Organism*>& toDie, std::vector<std::unique_ptr<Organism>>& toAdd) {
    auto& organisms = world.organisms; // zakładamy, że organisms jest publiczny lub udostępniony przez getter
    std::set<Organism*> alreadyReproduced;
    // Zwierzęta
    for (auto& org : organisms) {
        if (toDie.count(org.get())) continue;
        auto* animal = dynamic_cast<Animal*>(org.get());
        if (!animal || !animal->canReproduce() || alreadyReproduced.count(org.get())) continue;
        for (auto& other : organisms) {
            if (other.get() == org.get() || toDie.count(other.get()) || other->getSpecies() != org->getSpecies()) continue;
            auto* partner = dynamic_cast<Animal*>(other.get());
            if (!partner || !partner->canReproduce() || alreadyReproduced.count(other.get())) continue;
            int dx = abs(org->getPosition().getX() - other->getPosition().getX());
            int dy = abs(org->getPosition().getY() - other->getPosition().getY());
            if ((dx == 1 && dy == 0) || (dx == 0 && dy == 1)) {
                std::vector<Position> freePositions = world.getVectorOfFreePositionsAround(org->getPosition());
                if (freePositions.empty()) continue;
                int idx = rand() % freePositions.size();
                if (org->getSpecies() == "S") {
                    toAdd.push_back(std::make_unique<Sheep>(freePositions[idx]));
                } else if (org->getSpecies() == "W") {
                    toAdd.push_back(std::make_unique<Wolf>(freePositions[idx]));
                }
                animal->reproduce();
                partner->reproduce();
                alreadyReproduced.insert(org.get());
                alreadyReproduced.insert(other.get());
                break;
            }
        }
    }
    // Rośliny
    for (auto& org : organisms) {
        if (toDie.count(org.get())) continue;
        auto* plant = dynamic_cast<Plant*>(org.get());
        if (plant && plant->canReproduce()) {
            std::vector<Position> freePositions = world.getVectorOfFreePositionsAround(org->getPosition());
            if (freePositions.empty()) continue;
            int idx = rand() % freePositions.size();
            if (org->getSpecies() == "D") {
                toAdd.push_back(std::make_unique<Dandelion>(freePositions[idx]));
            } else if (org->getSpecies() == "T") {
                toAdd.push_back(std::make_unique<Toadstool>(freePositions[idx]));
            }
            org->reproduce();
        }
    }
}

