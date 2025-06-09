#pragma once
#include "../Abstractions/Animal.h"
#include <unordered_map>
#include <string>
#include "../Abstractions/Eating.h"

using namespace std;

class Sheep : public Animal
{
	protected:
		std::unordered_map<std::string, bool> diet;
	public:
		Sheep(Position position);
		~Sheep() override = default;
		std::string serialize() const override;
		static std::unique_ptr<Sheep> deserialize(const std::string& line);
		std::string toString() const override;
		void eat(Organism* other, int currentTurn, World* world) override;

};
