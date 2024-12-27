#ifndef TEAM_MANAGER_HPP
#define TEAM_MANAGER_HPP

#include "Team.hpp"
#include <memory>
#include <unordered_map>
class TeamManager {
public:
  TeamManager() = default;
  void addTeam(Team& team);
  Team& getTeamById(int id);
private:
  std::unordered_map<int, std::shared_ptr<Team>> teams;
};

#endif // !TEAM_MANAGER_HPP
