#include "World.h"
#include "BoardRenderer.h"
#include "MovementManager.h"
#include "ReproductionManager.h"
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
#include "iostream"

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

int World::getWorldX() const { return this->worldX; }
void World::setWorldX(int worldX) { this->worldX = worldX; }
int World::getWorldY() const { return this->worldY; }
void World::setWorldY(int worldY) { this->worldY = worldY; }
int World::getTurn() const { return this->turn; }

void World::addOrganism(std::unique_ptr<Organism> organism) {
    organism->setId(nextOrganismId++);
    if (organism->getBirthTurn() == -1) {
        organism->setBirthTurn(turn);
    }
    organisms.push_back(std::move(organism));
}

void World::removeOrganism(Organism* organism) {
    organisms.erase(std::remove_if(organisms.begin(), organisms.end(),
        [organism](const std::unique_ptr<Organism>& ptr) { return ptr.get() == organism; }), organisms.end());
}

void World::makeTurn() {
    toDie.clear(); 
    std::vector<std::unique_ptr<Organism>> toAdd;

    MovementManager::processMovements(*this, toDie);
    ReproductionManager::processReproduction(*this, toDie, toAdd);

    for (auto& org : organisms) {
        if (toDie.count(org.get())) continue;
        org->setLiveLength(org->getLiveLength() - 1);
        if (org->getLiveLength() == 0) {
            toDie.insert(org.get());
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
            if (type == "S") org = Sheep::deserialize(line);
            else if (type == "W") org = Wolf::deserialize(line);
            else if (type == "T") org = Toadstool::deserialize(line);
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

std::string World::boardToString() {
    return BoardRenderer::render(*this);
}
