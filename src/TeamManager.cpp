#include "TeamManager.hpp"
#include "Team.hpp"
#include <memory>

void TeamManager::addTeam(Team& team) {
  teams[team.id] = std::make_shared<Team>(team);
}

Team& TeamManager::getTeamById(int id) {
  return *teams[id];
}
