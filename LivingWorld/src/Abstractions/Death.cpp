#include "Death.h"
#include "../World/World.h"

void Death::execute(Organism* organism, int currentTurn, World* world) {
    if (!organism || !world) return;

    std::vector<Organism*> descendants;
        int parentId = organism->getId();
        for (auto* candidate : world->getAllOrganisms()) {
            const auto& history = candidate->getAncestryHistory();
            if (!history.empty() && history.back().first == parentId) {
                descendants.push_back(candidate);
            }
        }

    for (auto* descendant : descendants) {
        std::vector<std::pair<int, int>> history = descendant->getAncestryHistory();
        if (!history.empty()) {
            history.back().second = currentTurn;
            descendant->setAncestryHistory(history);
        }
    }
}
