#pragma once
#include "../Abstractions/Animal.h"
#include <unordered_map>
#include <string>
#include "../Abstractions/Eating.h"

using namespace std;

class Sheep : public Animal
{
	public:
		Sheep(Position position);
		Sheep(Position position, std::vector<std::pair<int, int>> ancestryHistory);
		~Sheep() override = default;
		std::string serialize() const override;
		static std::unique_ptr<Sheep> deserialize(const std::string& line);
		std::string toString() const override;
};
