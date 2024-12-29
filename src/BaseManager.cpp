#include "BaseManager.hpp"
#include <iostream>

BaseManager& BaseManager::getInstance() {
    static BaseManager instance;
    return instance;
}

void BaseManager::addBase(int teamId, std::shared_ptr<Base> base) {
    if (bases.find(teamId) != bases.end()) {
        std::cerr << "Error: Base for team ID " << teamId << " already exists!\n";
        return;
    }
    bases[teamId] = base;
}

std::shared_ptr<Base> BaseManager::getBaseByTeamId(int teamId) const {
    auto it = bases.find(teamId);
    if (it != bases.end()) {
        return it->second;
    }
    std::cerr << "Error: Base for team ID " << teamId << " not found!\n";
    return nullptr;
}

const std::unordered_map<int, std::shared_ptr<Base>>& BaseManager::getAllBases() const {
    return bases;
}

void BaseManager::printBases() const {
    for (const auto& [teamId, base] : bases) {
        std::cout << "Team ID: " << teamId << ", Base: " << base->toString() << "\n";
    }
}
