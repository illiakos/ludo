#ifndef TEAM_MANAGER_HPP
#define TEAM_MANAGER_HPP

#include "Team.hpp"
#include <memory>
#include <unordered_map>
class TeamManager {
public:
  static TeamManager &getInstance();
  void addTeam(Team &team);
  Team &getTeamById(int id);
  void addPointsToTeam(int teamId, int points);

private:
  std::unordered_map<int, std::shared_ptr<Team>> teams;
  std::unordered_map<int, int> pointsTable;
  TeamManager() = default;
  TeamManager(const TeamManager &) = delete;
  TeamManager &operator=(const TeamManager &) = delete;

  void writePointsTableToFile(const std::string &fileName);
};

#endif // !TEAM_MANAGER_HPP
