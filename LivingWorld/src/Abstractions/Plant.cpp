#include "Plant.h"
#include "Death.h"
#include "iostream"

Plant::Plant(int power, Position position, std::vector<std::pair<int, int>> ancestryHistory, int initiative, int liveLength, int powerToReproduce)
    : Organism(power, position, ancestryHistory, initiative, liveLength, powerToReproduce)
{
    setSpecies("P");
}


bool Plant::canReproduce() {
    return getPower() == powerToReproduce;
}
void Plant::reproduce() {setPower(getPower() / 2);}
bool Plant::canEat(Organism *other) {return false;}

