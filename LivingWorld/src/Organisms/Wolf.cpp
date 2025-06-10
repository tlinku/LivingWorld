#include "Wolf.h"
#include "sstream"
#include "../World/World.h"
#include "Toadstool.h"
#include "Sheep.h"
#include "../Abstractions/Death.h"

Wolf::Wolf(Position position)
    : Animal(8, position, {}, 5, 20, 16)
{
    setSpecies("W");
    diet = {
        {"S", true},
        {"W", false},
        {"D", false},
        {"T", true}
    };
}
Wolf::Wolf(Position position, std::vector<std::pair<int, int>> ancestryHistory)
    : Animal(8, position, ancestryHistory, 5, 15, 12)
{
    setSpecies("W");
    diet = {
        {"S", true},
        {"W", false},
        {"D", true},
        {"T", true}
    };
}

std::string Wolf::serialize() const {
    std::ostringstream oss;
    oss << "Wolf "
        << getPower() << ' '
        << getPosition().getX() << ' ' << getPosition().getY() << ' '
        << getInitiative() << ' '
        << getLiveLength() << ' '
        << powerToReproduce << ' ';
    const auto& history = getAncestryHistory();
    oss << history.size();
    for (const auto& entry : history) {
        oss << ' ' << entry.first << ' ' << entry.second;
    }
    return oss.str();
}

std::unique_ptr<Wolf> Wolf::deserialize(const std::string& line) {
    std::istringstream iss(line);
    std::string type;
    int power, x, y, initiative, liveLength, powerToReproduce, historySize;
    iss >> type >> power >> x >> y >> initiative >> liveLength >> powerToReproduce >> historySize;
    std::vector<std::pair<int, int>> ancestryHistory;
    for (int i = 0; i < historySize; ++i) {
        int birth, death;
        iss >> birth >> death;
        ancestryHistory.emplace_back(birth, death);
    }
    auto wolf = std::make_unique<Wolf>(Position(x, y));
    wolf->setPower(power);
    wolf->setInitiative(initiative);
    wolf->setLiveLength(liveLength);
    wolf->powerToReproduce = powerToReproduce;
    wolf->setAncestryHistory(ancestryHistory);
    return wolf;
}

std::string Wolf::toString() const {
    return "Wolf at (" + std::to_string(getPosition().getX()) + ", " + std::to_string(getPosition().getY()) + ") with power: " + std::to_string(getPower());
}

