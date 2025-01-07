#include "SpecialTiles.hpp"
#include "ColorConstants.hpp"
#include "MapDrawer.hpp"
#include "TeamManager.hpp"
#include "stb_image.h"
#include <iostream>
#include <ostream>

bool FinishingTile::getIsFinish() { return isFinish; }

/*int PrefinishingTile::getNextPosition () {*/
/*  return nextPosition;*/
/*}*/

void PrefinishingTile::setFirstFinishingTilePosition(int p) {
  firstFinishingTilePosition = p;
}

int PrefinishingTile::getFirstFinishingTilePosition() {
  return firstFinishingTilePosition;
}

int PrefinishingTile::getTeamId() { return teamId; }

void SafeTile::renderSelf() const {
  auto &drawer = MapDrawer::getInstance();
  const float cellSize = drawer.getCellSize();
  const float outerRadius = cellSize / 4;
  const float innerRadius = cellSize / 2;
  drawer.drawRectangle(drawer.getCellPosition(dimensions.x),
                       drawer.getCellPosition(dimensions.y), cellSize, cellSize,
                       white, FILLED_WITH_STROKE, gray, 2.0);
  drawer.drawStar(drawer.getCellPosition(dimensions.x) + cellSize / 2,
                  drawer.getCellPosition(dimensions.y) + cellSize / 2,
                  outerRadius, innerRadius, 5, starColor);
}

StartingTile::~StartingTile() {}

void StartingTile::renderSelf() const {

  auto &tm = TeamManager::getInstance();
  auto currentTeam = tm.getTeamById(teamId);
  auto &drawer = MapDrawer::getInstance();
  drawer.drawRectangle(drawer.getCellPosition(dimensions.x),
                       drawer.getCellPosition(dimensions.y),
                       drawer.getSizeOfCells(1), drawer.getSizeOfCells(1),
                       currentTeam.color);
}

FinishingTile::~FinishingTile() {}

void FinishingTile::renderSelf() const {
  auto &drawer = MapDrawer::getInstance();
  drawer.drawRectangle(drawer.getCellPosition(dimensions.x),
                       drawer.getCellPosition(dimensions.y),
                       drawer.getSizeOfCells(1), drawer.getSizeOfCells(1),
                       color);
}

PrefinishingTile::~PrefinishingTile() {}

void PrefinishingTile::renderSelf() const {
  auto &tm = TeamManager::getInstance();
  auto currentTeam = tm.getTeamById(teamId);
  auto &drawer = MapDrawer::getInstance();

  drawer.drawRectangle(drawer.getCellPosition(dimensions.x),
                       drawer.getCellPosition(dimensions.y),
                       drawer.getSizeOfCells(1), drawer.getSizeOfCells(1),
                       currentTeam.color);
}

SafeTile::~SafeTile() {}

TransitionTile::~TransitionTile() {}

void TransitionTile::renderSelf() const {
    auto &drawer = MapDrawer::getInstance();
    const float cellSize = drawer.getSizeOfCells(1);
    int arrowWidth, arrowHeight, arrowChannels;
    unsigned char *arrowData =
        stbi_load("../src/assets/images/arrow.png", &arrowWidth, &arrowHeight,
                  &arrowChannels, 4);

    if (!arrowData) {
        std::cerr << "Failed to load arrow image!" << std::endl;
    } else {
        // Determine rotation based on team ID
        cout << teamId << endl;
        float rotation = 0.0f;
        switch (teamId) {
            case 1: rotation = 270.0f; break;   // Red
            case 2: rotation = 0.0f; break; // Blue
            case 3: rotation = 180.0f; break; // Green
            case 4: rotation = 90.0f; break; // Yellow
            default: break; // Default is up
        }

        // Draw the arrow
        drawer.drawArrow(arrowData, arrowWidth, arrowHeight, arrowChannels,
                         drawer.getCellPosition(dimensions.x),
                         drawer.getCellPosition(dimensions.y), cellSize, cellSize,
                         rotation);

        // Free the arrow image data
        stbi_image_free(arrowData);
    }
}
