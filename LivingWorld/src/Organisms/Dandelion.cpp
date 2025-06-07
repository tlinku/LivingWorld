#include "Dandelion.h"
#include "sstream"
Dandelion::Dandelion(Position position)
    : Plant(0, position, {}, 0, 6, 4)
{
    setSpecies("D");
}

std::string Dandelion::serialize() const {
    std::ostringstream oss;
    oss << "Dandelion "
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

std::unique_ptr<Dandelion> Dandelion::deserialize(const std::string& line) {
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
    auto dandelion = std::make_unique<Dandelion>(Position(x, y));
    dandelion->setPower(power);
    dandelion->setInitiative(initiative);
    dandelion->setLiveLength(liveLength);
    dandelion->powerToReproduce = powerToReproduce;
    dandelion->setAncestryHistory(ancestryHistory);
    return dandelion;
}

std::string Dandelion::toString() const {
    return "Dandelion at (" + std::to_string(getPosition().getX()) + ", " + std::to_string(getPosition().getY()) + ")";
}
