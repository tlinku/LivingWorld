#include "World.h"
#include <fstream>
#include <algorithm>
#include <random>
#include <memory>
#include <sstream>
#include "../Organisms/Sheep.h"
#include "../Organisms/Wolf.h"
#include "../Organisms/Toadstool.h"
#include "../Organisms/Dandelion.h"
#include <set>
#include <iostream>

std::string World::getOrganismFromPosition(int x, int y) {
    for (const auto& org : organisms) {
        if (org->getPosition().getX() == x && org->getPosition().getY() == y)
            return org->getSpecies();
    }
    return "";
}

bool World::isPositionOnWorld(int x, int y) {
    return (x >= 0 && y >= 0 && x < getWorldX() && y < getWorldY());
}

bool World::isPositionFree(Position position) {
    return this->getOrganismFromPosition(position.getX(), position.getY()).empty();
}

std::vector<Position> World::getVectorOfFreePositionsAround(Position position) {
    int pos_x = position.getX(), pos_y = position.getY();
    std::vector<Position> result;
    for(int x = -1; x < 2; ++x)
        for (int y = -1; y < 2; ++y)
            if ((x != 0 || y != 0) && isPositionOnWorld(pos_x + x, pos_y + y)) {
                result.push_back(Position(pos_x + x, pos_y + y));
            }
    auto iter = std::remove_if(result.begin(), result.end(),
        [this](Position pos) {return !isPositionFree(pos); });
    result.erase(iter, result.end());
    return result;
}

World::World(int worldX, int worldY) {
    setWorldX(worldX);
    setWorldY(worldY);
}

int World::getWorldX() { return this->worldX; }
void World::setWorldX(int worldX) { this->worldX = worldX; }
int World::getWorldY() { return this->worldY; }
void World::setWorldY(int worldY) { this->worldY = worldY; }
int World::getTurn() { return this->turn; }

void World::addOrganism(std::unique_ptr<Organism> organism) {
    organism->setId(nextOrganismId++);
    organisms.push_back(std::move(organism));
}

void World::removeOrganism(Organism* organism) {
    organisms.erase(std::remove_if(organisms.begin(), organisms.end(),
        [organism](const std::unique_ptr<Organism>& ptr) { return ptr.get() == organism; }), organisms.end());
}

void World::makeTurn() {
    std::vector<Organism*> toDie;
    std::vector<std::unique_ptr<Organism>> toAdd;

    for (auto& org : organisms) {
        org->setPower(org->getPower()+1);
        auto* animal = dynamic_cast<Animal*>(org.get());
        if (animal) {
            Organism* bestFood = nullptr;
            int minDist = 1000000;
            for (auto& other : organisms) {
                if (other.get() != org.get() && animal->canEat(other.get())) {
                    int dist = abs(other->getPosition().getX() - org->getPosition().getX()) + abs(other->getPosition().getY() - org->getPosition().getY());
                    if (dist < minDist) {
                        minDist = dist;
                        bestFood = other.get();
                    }
                }
            }
            if (bestFood) {
                int dx = (bestFood->getPosition().getX() > org->getPosition().getX()) ? 1 : (bestFood->getPosition().getX() < org->getPosition().getX() ? -1 : 0);
                int dy = (bestFood->getPosition().getY() > org->getPosition().getY()) ? 1 : (bestFood->getPosition().getY() < org->getPosition().getY() ? -1 : 0);
                Position newPos(org->getPosition().getX() + dx, org->getPosition().getY() + dy);
                if (isPositionOnWorld(newPos.getX(), newPos.getY()) && isPositionFree(newPos)) {
                    animal->move(dx, dy);
                }
                if (org->getPosition().getX() == bestFood->getPosition().getX() && org->getPosition().getY() == bestFood->getPosition().getY()) {
                    animal->eat(bestFood, turn, this);
                    toDie.push_back(bestFood);
                }
            } else {
                std::vector<Position> freePositions = getVectorOfFreePositionsAround(org->getPosition());
                if (!freePositions.empty()) {
                    int idx = rand() % freePositions.size();
                    animal->move(freePositions[idx].getX() - org->getPosition().getX(),
                                 freePositions[idx].getY() - org->getPosition().getY());
                }
            }
        }
    }

    std::set<Organism*> alreadyReproduced;
    for (auto& org : organisms) {
        auto* animal = dynamic_cast<Animal*>(org.get());
        if (!animal || !animal->canReproduce() || alreadyReproduced.count(org.get())) continue;
        for (auto& other : organisms) {
            if (other.get() == org.get() || other->getSpecies() != org->getSpecies()) continue;
            auto* partner = dynamic_cast<Animal*>(other.get());
            if (!partner || !partner->canReproduce() || alreadyReproduced.count(other.get())) continue;
            int dx = abs(org->getPosition().getX() - other->getPosition().getX());
            int dy = abs(org->getPosition().getY() - other->getPosition().getY());
            if ((dx == 1 && dy == 0) || (dx == 0 && dy == 1)) {
                std::vector<Position> freePositions = getVectorOfFreePositionsAround(org->getPosition());
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

    for (auto& org : organisms) {
        auto* plant = dynamic_cast<Plant*>(org.get());
        if (plant && plant->canReproduce()) {
            std::vector<Position> freePositions = getVectorOfFreePositionsAround(org->getPosition());
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

    for (auto& org : organisms) {
        org->setLiveLength(org->getLiveLength() - 1);
        if (org->getLiveLength() == 0) {
            toDie.push_back(org.get());
        }
    }

    for (Organism* org : toDie) {
        removeOrganism(org);
    }
    for (auto& org : toAdd) {
        addOrganism(std::move(org));
    }
    ++turn;
}

void World::writeWorld(const std::string& fileName) {
    std::ofstream my_file(fileName);
    if (my_file.is_open()) {
        my_file << worldX << ' ' << worldY << ' ' << turn << '\n';
        my_file << organisms.size() << '\n';
        for (const auto& org : organisms) {
            my_file << org->serialize() << '\n';
        }
        my_file.close();
    }
}

void World::readWorld(const std::string& fileName) {
    std::ifstream my_file(fileName);
    if (my_file.is_open()) {
        organisms.clear();
        my_file >> worldX >> worldY >> turn;
        size_t orgs_size;
        my_file >> orgs_size;
        std::string line;
        std::getline(my_file, line);
        for (size_t i = 0; i < orgs_size; ++i) {
            std::getline(my_file, line);
            std::istringstream iss(line);
            std::string type;
            iss >> type;
            std::unique_ptr<Organism> org;
            if (type == "Sheep") org = Sheep::deserialize(line);
            else if (type == "Wolf") org = Wolf::deserialize(line);
            else if (type == "Toadstool") org = Toadstool::deserialize(line);
            if (org) organisms.push_back(std::move(org));
        }
        my_file.close();
    }
}

std::string World::toString() {
    std::ostringstream oss;
    oss << "World: " << worldX << "x" << worldY << ", turn: " << turn << "\n";
    for (const auto& org : organisms) {
        oss << org->toString() << "\n";
    }
    return oss.str();
}

std::vector<Organism*> World::getAllOrganisms() const {
    std::vector<Organism*> result;
    for (const auto& org : organisms) {
        result.push_back(org.get());
    }
    return result;
}
