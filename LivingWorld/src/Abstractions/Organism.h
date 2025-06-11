#pragma once

#include <string>
#include <vector>
#include "Position.h"

class World;

class Organism
{
protected:
	int power;
	Position position;
	std::string species;
	int initiative;
	int liveLength;
	int powerToReproduce;
	std::string sign;
	std::vector<std::pair<int, int>> ancestryHistory;

protected:
    int id = -1;
    int parentId = -1;
    int birthTurn = -1;

public:
	virtual ~Organism() = default;
	Organism(int power, Position position,
			 const std::vector<std::pair<int, int>>& ancestryHistory,
			 int initiative, int liveLength, int powerToReproduce);
	Organism(const Organism& other);
	Organism(Organism&& other) noexcept;
	Organism& operator=(const Organism& other);
	Organism& operator=(Organism&& other) noexcept;

	int getPower() const;
	void setPower(int power);

	Position getPosition() const;
	void setPosition(Position position);

	std::string getSpecies() const;
	void setSpecies(const std::string& spec);

	int getInitiative() const;
	void setInitiative(int initiative);

	int getLiveLength() const;
	void setLiveLength(int liveLength);

	void setAncestryHistory(const std::vector<std::pair<int, int>>& ancestryHistory);
	void addAncestor(int birthTurn, int deathTurn);
	std::vector<std::pair<int, int>> getAncestryHistory() const;

    int getId() const;
    void setId(int newId);
    int getParentId() const;
    void setParentId(int newParentId);
    int getBirthTurn() const;
    void setBirthTurn(int newBirthTurn);

	virtual std::string toString() const = 0;
    virtual bool canReproduce() const { return false; }
    virtual void reproduce() {}
    virtual std::string serialize() const { return ""; }
    static std::unique_ptr<Organism> deserialize(const std::string&) { return nullptr; }
};
