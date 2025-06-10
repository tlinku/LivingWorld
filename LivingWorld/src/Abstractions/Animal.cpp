#include "Animal.h"

#include "Death.h"
#include "../World/World.h"
#include "../Organisms/Toadstool.h"

Animal::Animal(int power, Position position, vector<pair<int, int>> ancestryHistory, int initiative, int liveLength, int powerToReproduce)
    : Organism(power, position, ancestryHistory, initiative, liveLength, powerToReproduce), lastPosition(position)
{
    setSpecies("A");
}

Position Animal::getLastPosition() const {
    return lastPosition;
}

void Animal::move(int dx, int dy)
{
    lastPosition = getPosition();
    setPosition(Position(lastPosition.getX() + dx, lastPosition.getY() + dy));
}

bool Animal::consumes(const std::string& species) {
    auto it = diet.find(species);
    if (it != diet.end()) {
        return it->second;
    }
    return false;
}

bool Animal::canEat(Organism* other) {
    if (!other || other == this) return false;
    return consumes(other->getSpecies()) && this->getPower() > other->getPower();
}

void Animal::eat(Organism* other, int currentTurn, World* world) {
    if (!other || !world) return;
    if (auto* toadstool = dynamic_cast<Toadstool*>(other)) {
        toadstool->onEatenBy(this, currentTurn, world);
        return;
    }
    if (canEat(other)) {
        setPower(getPower() + 1);
        Death::execute(other, currentTurn, world);
    }
}


bool Animal::canReproduce() {
    return getPower() >= powerToReproduce;
}

void Animal::reproduce() {
    setPower(getPower() / 2);
}
