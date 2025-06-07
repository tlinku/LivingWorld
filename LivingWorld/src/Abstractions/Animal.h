#pragma once

#include "Moveable.h"
#include "Organism.h"
#include "Eating.h"
#include "Reproduction.h"
#include <unordered_map>
#include <string>

class World;

class Animal : public Organism, public Moveable, public Eating, public Reproduction
{
protected:
    Position lastPosition;
    std::unordered_map<std::string, bool> diet;

public:
    Animal(int power, Position position, std::vector<std::pair<int, int>> ancestryHistory, int initiative, int liveLength, int powerToReproduce);
    void move(int dx, int dy) override;
    Position getLastPosition() const;
    virtual bool consumes(const std::string& species);
    bool canEat(Organism* other) override;
    void eat(Organism* other, int currentTurn, World* world) override;
    bool canReproduce() override;
    void reproduce() override;

};
