#include "Toadstool.h"
#include "../Abstractions/Organism.h"
#include "../Abstractions/Death.h"
#include "../World/World.h"
#include "sstream"

Toadstool::Toadstool(Position position)
    : Plant(0, position, {}, 0, 8, 4)
{
    setSpecies("T");
}
void Toadstool::onEatenBy(Organism* eater, int currentTurn, World* world) {
    if (eater && world) {
        Death::execute(eater, currentTurn, world);
    }
    Death::execute(this, currentTurn, world);
}
std::unique_ptr<Toadstool> Toadstool::deserialize(const std::string& line) {
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
    auto toadstool = std::make_unique<Toadstool>(Position(x, y));
    toadstool->setPower(power);
    toadstool->setInitiative(initiative);
    toadstool->setLiveLength(liveLength);
    toadstool->powerToReproduce = powerToReproduce;
    toadstool->setAncestryHistory(ancestryHistory);
    return toadstool;
}
std::string Toadstool::toString() const {
    return "Toadstool at (" + std::to_string(getPosition().getX()) + ", " + std::to_string(getPosition().getY()) + ") with power: " + std::to_string(getPower());
}
std::string Toadstool::serialize() const {
    std::ostringstream oss;
    oss << "Toadstool "
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
