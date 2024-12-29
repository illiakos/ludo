#ifndef BASE_MANAGER_HPP
#define BASE_MANAGER_HPP

#include "Base.hpp"
#include <unordered_map>
#include <memory>
#include <vector>

class BaseManager {
public:
    // Singleton instance
    static BaseManager& getInstance();

    // Add a base
    void addBase(int teamId, std::shared_ptr<Base> base);

    // Get a base by team ID
    std::shared_ptr<Base> getBaseByTeamId(int teamId) const;

    // Get all bases
    const std::unordered_map<int, std::shared_ptr<Base>>& getAllBases() const;

    // Print all bases (for debugging)
    void printBases() const;

private:
    BaseManager() = default;
    BaseManager(const BaseManager&) = delete;
    BaseManager& operator=(const BaseManager&) = delete;

    std::unordered_map<int, std::shared_ptr<Base>> bases; // Maps team IDs to bases
};

#endif // BASE_MANAGER_HPP
