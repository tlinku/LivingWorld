#include "Animal.h"

Animal::Animal(int power, Position position, vector<pair<int, int>> ancestryHistory, int initiative, int liveLength)
    : Organism(power, position, ancestryHistory, initiative, liveLength), lastPosition(position)
{
    setSpecies("A");
}

Animal::Animal() : Organism(), lastPosition(Position(0, 0))
{
    setSpecies("A");
}

Position Animal::getLastPosition() const {
    return lastPosition;
}

void Animal::move(int dx, int dy)
{
    lastPosition = getPosition();
    Organism::move(dx, dy); 
}