#pragma once
#include "../Abstractions/Animal.h"
#include <unordered_map>
#include <string>

using namespace std;

class Wolf : public Animal
{
public:
    Wolf(Position position);
    virtual ~Wolf() override = default;
    std::string serialize() const override;
    static std::unique_ptr<Wolf> deserialize(const std::string& line);
    std::string toString() const override;
    void eat(Organism* other, int currentTurn, World* world) override;
};