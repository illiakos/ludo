#include "TeamManager.hpp"
#include "EventLoop.hpp"
#include "StopGameEvent.hpp"
#include "Team.hpp"
#include <fstream>
#include <iostream>
#include <memory>

TeamManager &TeamManager::getInstance() {
  static TeamManager instance;
  return instance;
}

TeamManager::TeamManager() {
  pointsTable[1] = 0;
  pointsTable[2] = 0;
  pointsTable[3] = 0;
  pointsTable[4] = 0;
}

void TeamManager::addTeam(Team &team) {
  teams[team.id] = std::make_shared<Team>(team);
}

Team &TeamManager::getTeamById(int id) { return *teams[id]; }

void TeamManager::addPointsToTeam(int teamId, int points) {
  if (pointsTable.find(teamId) == pointsTable.end()) {
    throw std::runtime_error("Team not found in points table");
  }

  pointsTable[teamId] += points;
  std::cout << "Added " << points << " points to team ID " << teamId
            << ". Total points: " << pointsTable[teamId] << "\n";

  // Check if the team has reached or exceeded 4 points
  if (pointsTable[teamId] >= 4) {
    std::cout << "Team ID " << teamId << " has reached 4 or more points.\n";
    writePointsTableToFile("points_table.txt");
    auto loop = EventLoop::getInstance();
    loop->enqueueEvent(std::make_shared<StopGameEvent>());
  }
}

void TeamManager::writePointsTableToFile(const std::string &fileName) {
  std::ofstream outFile(fileName);
  if (!outFile.is_open()) {
    throw std::runtime_error("Failed to open file for writing");
  }

  outFile << "Points Table:\n";
  for (const auto &entry : pointsTable) {
    outFile << "Team ID: " << entry.first << ", Points: " << entry.second
            << "\n";
  }

  outFile.close();
  std::cout << "Points table written to " << fileName << "\n";
}
