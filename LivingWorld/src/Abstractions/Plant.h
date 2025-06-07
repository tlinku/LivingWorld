#pragma once
#include "Organism.h"
#include "Reproduction.h"
class Plant : public Organism, public Reproduction
{
public:
	Plant(int power, Position position, std::vector<std::pair<int, int>> ancestryHistory, int initiative, int liveLength, int powerToReproduce);
	bool canReproduce() override;
	void reproduce() override;
	bool canEat(Organism* other);
};
