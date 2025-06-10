#include "MovementManager.h"
#include <vector>
#include "../Abstractions/Plant.h"

void MovementManager::processMovements(World& world, std::set<Organism*>& toDie) {
    auto& organisms = world.organisms; // zakładamy, że organisms jest publiczny lub udostępniony przez getter
    int turn = world.getTurn();
    int orgIdx = 0;
    for (auto& org : organisms) {
        if (toDie.count(org.get())) { orgIdx++; continue; }
        org->setPower(org->getPower()+1);
        auto* animal = dynamic_cast<Animal*>(org.get());
        if (animal) {
            bool ate = false;
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if ((dx != 0 || dy != 0) && (abs(dx) + abs(dy) == 1)) {
                        Position checkPos(org->getPosition().getX() + dx, org->getPosition().getY() + dy);
                        if (world.isPositionOnWorld(checkPos.getX(), checkPos.getY())) {
                            for (auto& other : organisms) {
                                if (other.get() != org.get() && !toDie.count(other.get()) && other->getPosition() == checkPos && animal->canEat(other.get())) {
                                    animal->move(dx, dy);
                                    animal->eat(other.get(), turn, &world);
                                    toDie.insert(other.get());
                                    ate = true;
                                    break;
                                }
                            }
                        }
                        if (ate) break;
                    }
                }
                if (ate) break;
            }
            if (ate) { orgIdx++; continue; }
            if (animal->getPower() >= animal->getPowerToReproduce() && animal->canReproduce()) {
                Organism* bestPartner = nullptr;
                int minDist = 1000000;
                for (auto& other : organisms) {
                    if (other.get() != org.get() && !toDie.count(other.get()) && other->getSpecies() == org->getSpecies()) {
                        auto* partner = dynamic_cast<Animal*>(other.get());
                        if (partner && partner->canReproduce() && partner->getPower() >= partner->getPowerToReproduce()) {
                            int dist = abs(other->getPosition().getX() - org->getPosition().getX()) + abs(other->getPosition().getY() - org->getPosition().getY());
                            if (dist < minDist) {
                                minDist = dist;
                                bestPartner = other.get();
                            }
                        }
                    }
                }
                if (bestPartner) {
                    int dx = (bestPartner->getPosition().getX() > org->getPosition().getX()) ? 1 : (bestPartner->getPosition().getX() < org->getPosition().getX() ? -1 : 0);
                    int dy = (bestPartner->getPosition().getY() > org->getPosition().getY()) ? 1 : (bestPartner->getPosition().getY() < org->getPosition().getY() ? -1 : 0);
                    Position newPos(org->getPosition().getX() + dx, org->getPosition().getY() + dy);
                    if (world.isPositionOnWorld(newPos.getX(), newPos.getY()) && world.isPositionFree(newPos)) {
                        animal->move(dx, dy);
                    }
                    orgIdx++;
                    continue;
                }
            }
            Organism* bestFood = nullptr;
            int minDist = 1000000;
            if (animal->getPower() < animal->getPowerToReproduce()) {
                for (auto& other : organisms) {
                    if (other.get() != org.get() && !toDie.count(other.get()) && animal->canEat(other.get())) {
                        int dist = abs(other->getPosition().getX() - org->getPosition().getX()) + abs(other->getPosition().getY() - org->getPosition().getY());
                        if (dist < minDist) {
                            minDist = dist;
                            bestFood = other.get();
                        }
                    }
                }
            }
            if (bestFood) {
                int dx = (bestFood->getPosition().getX() > org->getPosition().getX()) ? 1 : (bestFood->getPosition().getX() < org->getPosition().getX() ? -1 : 0);
                int dy = (bestFood->getPosition().getY() > org->getPosition().getY()) ? 1 : (bestFood->getPosition().getY() < org->getPosition().getY() ? -1 : 0);
                Position newPos(org->getPosition().getX() + dx, org->getPosition().getY() + dy);
                if (world.isPositionOnWorld(newPos.getX(), newPos.getY())) {
                    Organism* occupant = nullptr;
                    for (auto& other : organisms) {
                        if (other.get() != org.get() && !toDie.count(other.get()) && other->getPosition() == newPos) {
                            occupant = other.get();
                            break;
                        }
                    }
                    if (occupant == nullptr) {
                        // Pole wolne
                        animal->move(dx, dy);
                    } else if (animal->canEat(occupant)) {
                        // Pole zajęte przez jadalny organizm
                        animal->move(dx, dy);
                        animal->eat(occupant, turn, &world);
                        toDie.insert(occupant);
                    }
                }
            } else {
                std::vector<Position> freePositions = world.getVectorOfFreePositionsAround(org->getPosition());
                if (!freePositions.empty()) {
                    int idx = rand() % freePositions.size();
                    animal->move(freePositions[idx].getX() - org->getPosition().getX(),
                                 freePositions[idx].getY() - org->getPosition().getY());
                }
            }
        }
        orgIdx++;
    }
}
