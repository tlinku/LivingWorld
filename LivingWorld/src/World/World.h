#pragma once

#include <vector>
#include <memory>
#include <string>
#include "../Abstractions/Organism.h"

class World {
private:
    int worldX;
    int worldY;
    int turn = 0;
    std::vector<std::unique_ptr<Organism>> organisms;
    char separator = '.';
    int nextOrganismId = 1; // licznik do nadawania unikalnych id

    std::string getOrganismFromPosition(int x, int y);
    bool isPositionOnWorld(int x, int y);
    bool isPositionFree(Position position);

public:
    World(int worldX, int worldY);
    World() : World(6, 6) {}

    int getWorldX();
    void setWorldX(int worldX);
    int getWorldY();
    void setWorldY(int worldY);
    int getTurn();

    void addOrganism(std::unique_ptr<Organism> organism);
    void removeOrganism(Organism* organism);
    std::vector<Position> getVectorOfFreePositionsAround(Position position);
    void makeTurn();

    void writeWorld(const std::string& fileName);
    void readWorld(const std::string& fileName);
    std::string toString();
    std::vector<Organism*> getAllOrganisms() const;
};
