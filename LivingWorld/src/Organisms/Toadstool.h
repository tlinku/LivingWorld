#pragma once
#include "../Abstractions/Plant.h"
#include <string>
using namespace std;

class Toadstool : public Plant
{
public:
    Toadstool(Position position);
    Toadstool(Position position, std::vector<std::pair<int, int>> ancestryHistory);
    virtual ~Toadstool() override = default;
    void onEatenBy(Organism* eater, int currentTurn, World* world);
    std::string serialize() const override;
    static std::unique_ptr<Toadstool> deserialize(const std::string& line);
    std::string toString() const override;
};
