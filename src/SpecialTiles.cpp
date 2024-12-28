#include "SpecialTiles.hpp"
#include "MapDrawer.hpp"

bool FinishingTile::getIsFinish() {
  return isFinish;
}

int PrefinishingTile::getNextPosition() {
  return nextPosition;
}

void PrefinishingTile::setFirstFinishingTilePosition(int p) {
  firstFinishingTilePosition = p;
}

int PrefinishingTile::getFirstFinishingTilePosition() {
  return firstFinishingTilePosition;
}

int PrefinishingTile::getTeamId() {
  return teamId;
}

void SafeTile::renderSelf() const {
  auto drawer = MapDrawer::getInstance();
}

StartingTile::~StartingTile() {

}

void StartingTile::renderSelf() const {

}

FinishingTile::~FinishingTile() {

}

void FinishingTile::renderSelf() const {

}

PrefinishingTile::~PrefinishingTile() {

}

void PrefinishingTile::renderSelf() const {

}

SafeTile::~SafeTile() {
  
}