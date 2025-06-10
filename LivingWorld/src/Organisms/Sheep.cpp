#include "Sheep.h"
#include "sstream"
#include "../World/World.h"

Sheep::Sheep(Position position)
    : Animal(3, position, {}, 5, 12, 6)
{
    setSpecies("S");
    diet = {
        {"S", false},
        {"W", false},
        {"D", true},
        {"T", true}
    };
}
Sheep::Sheep(Position position, std::vector<std::pair<int, int>> ancestryHistory)
    : Animal(3, position, ancestryHistory, 5, 12, 6)
{
    setSpecies("S");
    diet = {
        {"S", false},
        {"W", false},
        {"D", true},
        {"T", true}
    };
}

std::string Sheep::serialize() const {
    std::ostringstream oss;
    oss << "Sheep "
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

std::unique_ptr<Sheep> Sheep::deserialize(const std::string& line) {
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
    auto sheep = std::make_unique<Sheep>(Position(x, y));
    sheep->setPower(power);
    sheep->setInitiative(initiative);
    sheep->setLiveLength(liveLength);
    sheep->powerToReproduce = powerToReproduce;
    sheep->setAncestryHistory(ancestryHistory);
    return sheep;
}

std::string Sheep::toString() const {
    return "Sheep at (" + std::to_string(getPosition().getX()) + ", " + std::to_string(getPosition().getY()) + ") with power: " + std::to_string(getPower());
}
