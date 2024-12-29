#include "SpecialTiles.hpp"
#include "ColorConstants.hpp"
#include "MapDrawer.hpp"
#include "TeamManager.hpp"
#include <iostream>
#include <ostream>

bool FinishingTile::getIsFinish() { return isFinish; }

int PrefinishingTile::getNextPosition() { return nextPosition; }

void PrefinishingTile::setFirstFinishingTilePosition(int p) {
  firstFinishingTilePosition = p;
}

int PrefinishingTile::getFirstFinishingTilePosition() {
  return firstFinishingTilePosition;
}

int PrefinishingTile::getTeamId() { return teamId; }

void SafeTile::renderSelf() const {

  auto &drawer = MapDrawer::getInstance();
  drawer.drawRectangle(dimensions.x, dimensions.y, dimensions.dx, dimensions.dy,
                       white, FILLED_WITH_STROKE, gray, 2.0);
}

StartingTile::~StartingTile() {}

void StartingTile::renderSelf() const {

  auto& tm = TeamManager::getInstance();
  auto currentTeam = tm.getTeamById(teamId);
  auto &drawer = MapDrawer::getInstance();
  std::cout << "rendering starting tile" << std::endl;
  std::cout << currentTeam.id << std::endl;
  drawer.drawRectangle(drawer.getCellPosition(dimensions.x),
                       drawer.getCellPosition(dimensions.y),
                       drawer.getSizeOfCells(1),
                       drawer.getSizeOfCells(1),
                       currentTeam.color);
}

FinishingTile::~FinishingTile() {}

void FinishingTile::renderSelf() const {}

PrefinishingTile::~PrefinishingTile() {}

void PrefinishingTile::renderSelf() const {
  auto &currentTeam = TeamManager::getInstance().getTeamById(teamId);
  auto &drawer = MapDrawer::getInstance();
  drawer.drawRectangle(dimensions.x, dimensions.y, dimensions.dx, dimensions.dy,
                       currentTeam.color, FILLED_WITH_STROKE, gray, 2.0);
}

SafeTile::~SafeTile() {}

TransitionTile::~TransitionTile() {}

void TransitionTile::renderSelf() const {
  auto &drawer = MapDrawer::getInstance();
  drawer.drawRectangle(dimensions.x, dimensions.y, dimensions.dx, dimensions.dy,
                       white, FILLED_WITH_STROKE, gray, 2.0);
}
