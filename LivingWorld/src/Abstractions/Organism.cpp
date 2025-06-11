#include "Organism.h"
#include <sstream>

Organism::Organism(int power, Position position,
                   const std::vector<std::pair<int, int>>& ancestryHistory,
                   int initiative, int liveLength, int powerToReproduce)
    : power(power),
      position(position),
      ancestryHistory(ancestryHistory),
      initiative(initiative),
      liveLength(liveLength),
      species("O"),
      powerToReproduce(powerToReproduce) {}

Organism::Organism(const Organism& other)
    : power(other.power),
      position(other.position),
      ancestryHistory(other.ancestryHistory),
      species(other.species),
      initiative(other.initiative),
      liveLength(other.liveLength),
      powerToReproduce(other.powerToReproduce),
      sign(other.sign),
      id(other.id),
      parentId(other.parentId),
      birthTurn(other.birthTurn) {}

Organism::Organism(Organism&& other) noexcept
    : power(other.power),
      position(std::move(other.position)),
      ancestryHistory(std::move(other.ancestryHistory)),
      species(std::move(other.species)),
      initiative(other.initiative),
      liveLength(other.liveLength),
      powerToReproduce(other.powerToReproduce),
      sign(std::move(other.sign)),
      id(other.id),
      parentId(other.parentId),
      birthTurn(other.birthTurn) {}

Organism& Organism::operator=(const Organism& other) {
    if (this != &other) {
        power = other.power;
        position = other.position;
        ancestryHistory = other.ancestryHistory;
        species = other.species;
        initiative = other.initiative;
        liveLength = other.liveLength;
        powerToReproduce = other.powerToReproduce;
        sign = other.sign;
        id = other.id;
        parentId = other.parentId;
        birthTurn = other.birthTurn;
    }
    return *this;
}

Organism& Organism::operator=(Organism&& other) noexcept {
    if (this != &other) {
        power = other.power;
        position = std::move(other.position);
        ancestryHistory = std::move(other.ancestryHistory);
        species = std::move(other.species);
        initiative = other.initiative;
        liveLength = other.liveLength;
        powerToReproduce = other.powerToReproduce;
        sign = std::move(other.sign);
        id = other.id;
        parentId = other.parentId;
        birthTurn = other.birthTurn;
    }
    return *this;
}

void Organism::addAncestor(int birthTurn, int deathTurn) {
    ancestryHistory.emplace_back(birthTurn, deathTurn);
}

int Organism::getPower() const {
    return power;
}

void Organism::setPower(int power) {
    this->power = power;
}

Position Organism::getPosition() const {
    return position;
}

void Organism::setPosition(Position position) {
    this->position = position;
}

std::string Organism::getSpecies() const {
    return species;
}

void Organism::setSpecies(const std::string& spec) {
    this->species = spec;
}

int Organism::getInitiative() const {
    return initiative;
}

void Organism::setInitiative(int initiative) {
    this->initiative = initiative;
}

int Organism::getLiveLength() const {
    return liveLength;
}

void Organism::setLiveLength(int liveLength) {
    this->liveLength = liveLength;
}

void Organism::setAncestryHistory(const std::vector<std::pair<int, int>>& ancestryHistory) {
    this->ancestryHistory = ancestryHistory;
}

std::vector<std::pair<int, int>> Organism::getAncestryHistory() const {
    return ancestryHistory;
}

int Organism::getId() const {
    return id;
}

void Organism::setId(int newId) {
    id = newId;
}

int Organism::getParentId() const {
    return parentId;
}

void Organism::setParentId(int newParentId) {
    parentId = newParentId;
}

int Organism::getBirthTurn() const {
    return birthTurn;
}

void Organism::setBirthTurn(int newBirthTurn) {
    birthTurn = newBirthTurn;
}
