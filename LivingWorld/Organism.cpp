#include "Organism.h"

Organism::Organism(int power, Position position, vector<pair<int, int>> ancestryHistory, int initive, int liveLengh)
{
	setPower(power);
	setPosition(position);
	setAncestryHistory(ancestryHistory);
	setSpecies("O");
	setInitiative(initive);
	setLiveLength(liveLength);
}
Organism::Organism(const Organism& other)
	: power(other.power), position(other.position),
	  ancestryHistory(other.ancestryHistory), species(other.species) {}

Organism::Organism(Organism&& other) noexcept
	: power(other.power), position(std::move(other.position)),
	  ancestryHistory(std::move(other.ancestryHistory)), species(std::move(other.species)) {}

Organism& Organism::operator=(const Organism& other) {
	if (this != &other) {
		power = other.power;
		position = other.position;
		ancestryHistory = other.ancestryHistory;
		species = other.species;
	}
	return *this;
}

Organism& Organism::operator=(Organism&& other) noexcept {
	if (this != &other) {
		power = other.power;
		position = std::move(other.position);
		ancestryHistory = std::move(other.ancestryHistory);
		species = std::move(other.species);
	}
	return *this;
}

Organism::~Organism() = default;

void Organism::addAncestor(int birthTurn, int deathTurn) {
	ancestryHistory.emplace_back(birthTurn, deathTurn);
}

void Organism::setInitiative(int initiative) {
	this->initiative = initiative;
}
void Organism::setLiveLength(int liveLength) {
	this->liveLength = liveLength;
}


int Organism::getPower()
{
	return this->power;
}

void Organism::setPower(int power)
{
	this->power = power;
}

Position Organism::getPosition()
{
	return this->position;
}

void Organism::setPosition(Position position)
{
	this->position = position;
}
void Organism::setAncestryHistory(vector<pair<int, int>> ancestryHistory)
{
	this->ancestryHistory = ancestryHistory;
}
vector<pair<int, int>> Organism::getAncestryHistory()
{
	return this->ancestryHistory;
}

string Organism::toString()
{
	return "{ species: " + this->getSpecies() + 
		", power: " + to_string(getPower()) + 
		", position: " + getPosition().toString() + "}";
}

void Organism::move(int dx, int dy)
{
	position.move(dx, dy);
}

string Organism::getSpecies()
{
	return this->species;
}

void Organism::setSpecies(string spec)
{
	this->species = spec;
}
