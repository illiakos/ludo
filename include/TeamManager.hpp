#ifndef TEAM_MANAGER_HPP
#define TEAM_MANAGER_HPP

#include "Team.hpp"
#include <memory>
#include <unordered_map>
class TeamManager {
public:
  static TeamManager &getInstance ();
  void addTeam (Team &team);
  Team &getTeamById (int id);

private:
  std::unordered_map<int, std::shared_ptr<Team>> teams;

  TeamManager () = default;
  TeamManager (const TeamManager &) = delete;
  TeamManager &operator= (const TeamManager &) = delete;
};

#endif // !TEAM_MANAGER_HPP
