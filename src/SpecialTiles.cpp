#include "SpecialTiles.hpp"
#include "ColorConstants.hpp"
#include "MapDrawer.hpp"
#include "TeamManager.hpp"
#include <iostream>
#include <ostream>

bool FinishingTile::getIsFinish () {
  return isFinish;
}

int PrefinishingTile::getNextPosition () {
  return nextPosition;
}

void PrefinishingTile::setFirstFinishingTilePosition (int p) {
  firstFinishingTilePosition = p;
}

int PrefinishingTile::getFirstFinishingTilePosition () {
  return firstFinishingTilePosition;
}

int PrefinishingTile::getTeamId () {
  return teamId;
}

void SafeTile::renderSelf () const {
  auto &drawer = MapDrawer::getInstance ();
  const float cellSize = drawer.getCellSize ();
  const float outerRadius = cellSize / 4;
  const float innerRadius = cellSize / 2;
  drawer.drawRectangle (drawer.getCellPosition (dimensions.x),
      drawer.getCellPosition (dimensions.y),
      cellSize,
      cellSize,
      white,
      FILLED_WITH_STROKE,
      gray,
      2.0);
  drawer.drawStar (drawer.getCellPosition (dimensions.x) + cellSize / 2,
      drawer.getCellPosition (dimensions.y) + cellSize / 2,
      outerRadius,
      innerRadius,
      5,
      starColor);
}

StartingTile::~StartingTile () {
}

void StartingTile::renderSelf () const {

  auto &tm = TeamManager::getInstance ();
  auto currentTeam = tm.getTeamById (teamId);
  auto &drawer = MapDrawer::getInstance ();
  std::cout << "rendering starting tile" << std::endl;
  std::cout << currentTeam.id << std::endl;
  drawer.drawRectangle (drawer.getCellPosition (dimensions.x),
      drawer.getCellPosition (dimensions.y),
      drawer.getSizeOfCells (1),
      drawer.getSizeOfCells (1),
      currentTeam.color);
}

FinishingTile::~FinishingTile () {
}

void FinishingTile::renderSelf () const {
  auto &drawer = MapDrawer::getInstance ();
  drawer.drawRectangle (drawer.getCellPosition (dimensions.x),
      drawer.getCellPosition (dimensions.y),
      drawer.getSizeOfCells (1),
      drawer.getSizeOfCells (1),
      color);
}

PrefinishingTile::~PrefinishingTile () {
}

void PrefinishingTile::renderSelf () const {
  auto &tm = TeamManager::getInstance ();
  auto currentTeam = tm.getTeamById (teamId);
  auto &drawer = MapDrawer::getInstance ();

  std::cout << "rendering PrefinishingTile tile" << std::endl;
  std::cout << currentTeam.id << std::endl;

  drawer.drawRectangle (drawer.getCellPosition (dimensions.x),
      drawer.getCellPosition (dimensions.y),
      drawer.getSizeOfCells (1),
      drawer.getSizeOfCells (1),
      currentTeam.color);
}

SafeTile::~SafeTile () {
}

TransitionTile::~TransitionTile () {
}

void TransitionTile::renderSelf () const {
  auto &drawer = MapDrawer::getInstance ();
  const float cellSize = drawer.getCellSize ();
  const float headLength = cellSize / 2;
  const float headWidth = cellSize / 2;

  drawer.drawRectangle (drawer.getCellPosition (dimensions.x),
      drawer.getCellPosition (dimensions.y),
      cellSize,
      cellSize,
      white,
      FILLED_WITH_STROKE,
      gray,
      2.0);
  drawer.drawArrow (drawer.getCellPosition (dimensions.x),
      drawer.getCellPosition (dimensions.y),
      drawer.getCellPosition (dimensions.x) + cellSize,
      drawer.getCellPosition (dimensions.y) + cellSize,
      headLength,
      headWidth,
      color);
}
