#pragma once
#include <string>
#include "Position.h"
#include "World.h"
#include <vector>
using namespace std;

class Organism
{
private:
	int power;
	Position position;
	string species;
	int initiative;
	int liveLength;
	int powerToReproduce;
	string sign;
	World world;
	vector<pair<int, int>> ancestryHistory;

public:
	Organism(int power, Position position, vector<pair<int, int>> ancestryHistory, int initiative, int liveLength);
	Organism(const Organism& other);
	Organism(Organism&& other) noexcept;
	Organism& operator=(const Organism& other);
	Organism& operator=(Organism&& other) noexcept;
	virtual ~Organism();
	int getPower();
	void setPower(int power);
	Position getPosition();
	void setPosition(Position position);
	string getSpecies();
	void setSpecies(string spec);
	void setInitiative(int initiative);
	void setLiveLength(int liveLength);
	void setAncestryHistory(vector<pair<int, int>> ancestryHistory);
	void addAncestor(int birthTurn, int deathTurn);
	vector<pair<int, int>> getAncestryHistory();
	string toString();
	virtual void move(int dx, int dy);

};