#pragma once
#include "Organism.h"

using namespace std;

class Animal : public Organism
{
private:
    Position lastPosition;
public:
    Animal(int power, Position position, vector<pair<int, int>> ancestryHistory, int initiative, int liveLength);
    Animal();
    Position getLastPosition() const;
    void move(int dx, int dy) override;
};

