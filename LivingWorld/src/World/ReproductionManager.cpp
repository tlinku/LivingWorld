#include "ReproductionManager.h"
#include "../Organisms/Sheep.h"
#include "../Organisms/Wolf.h"
#include "../Organisms/Dandelion.h"
#include "../Organisms/Toadstool.h"
#include "../Abstractions/Plant.h"
#include <vector>
#include <set>

void ReproductionManager::processReproduction(World& world, std::set<Organism*>& toDie, std::vector<std::unique_ptr<Organism>>& toAdd) {
    auto& organisms = world.organisms; 
    std::set<Organism*> alreadyReproduced;
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
                std::vector<std::pair<int, int>> childHistory = animal->getAncestryHistory();
                childHistory.emplace_back(org->getBirthTurn(), -1);
                if (org->getSpecies() == "S") {
                    auto child = std::make_unique<Sheep>(freePositions[idx], childHistory);
                    child->setParentId(org->getId());
                    child->setBirthTurn(world.getTurn());
                    toAdd.push_back(std::move(child));
                } else if (org->getSpecies() == "W") {
                    auto child = std::make_unique<Wolf>(freePositions[idx], childHistory);
                    child->setParentId(org->getId());
                    child->setBirthTurn(world.getTurn());
                    toAdd.push_back(std::move(child));
                }
                animal->reproduce();
                partner->reproduce();
                alreadyReproduced.insert(org.get());
                alreadyReproduced.insert(other.get());
                break;
            }
        }
    }
    int dandelionCount = 0;
    int toadstoolCount = 0;
    for (auto& org : organisms) {
        if (toDie.count(org.get())) continue;
        auto* plant = dynamic_cast<Plant*>(org.get());
        if (plant && plant->canReproduce()) {
            if (org->getSpecies() == "D") dandelionCount++;
            if (org->getSpecies() == "T") toadstoolCount++;
        }
    }
    for (auto& org : organisms) {
        if (toDie.count(org.get())) continue;
        auto* plant = dynamic_cast<Plant*>(org.get());
        if (plant && plant->canReproduce()) {
            std::vector<Position> freePositions = world.getVectorOfFreePositionsAround(org->getPosition());
            if (freePositions.empty()) continue;
            int idx = rand() % freePositions.size();
            std::vector<std::pair<int, int>> childHistory = org->getAncestryHistory();
            childHistory.emplace_back(org->getBirthTurn(), -1);
            if (org->getSpecies() == "D" && dandelionCount < 20) {
                auto child = std::make_unique<Dandelion>(freePositions[idx], childHistory);
                child->setParentId(org->getId());
                child->setBirthTurn(world.getTurn());
                toAdd.push_back(std::move(child));
                dandelionCount++;
            } else if (org->getSpecies() == "T" && toadstoolCount < 10) {
                auto child = std::make_unique<Toadstool>(freePositions[idx], childHistory);
                child->setParentId(org->getId());
                child->setBirthTurn(world.getTurn());
                toAdd.push_back(std::move(child));
                toadstoolCount++;
            }
            org->reproduce();
        }
    }
}
