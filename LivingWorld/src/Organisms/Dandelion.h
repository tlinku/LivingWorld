#pragma once
#include "../Abstractions/Plant.h"
#include <string>
using namespace std;

class Dandelion : public Plant
{
public:
    Dandelion(Position position);
    std::string toString() const override;
    std::string serialize() const override;
    static std::unique_ptr<Dandelion> deserialize(const std::string& line);

};

