#include "Pawn.hpp"
#include "BaseManager.hpp"
#include "ColorConstants.hpp"
#include "EventLoop.hpp"
#include "MapDrawer.hpp"
#include "MovePawnEvent.hpp"
#include "TeamManager.hpp"
#include "TileContext.hpp"
#include "TurnManager.hpp"
#include "TileManager.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <memory>
#include <ostream>

using namespace std;

const int RENDER_PRECISION = 1000;

const double PI = 3.141592653589793;

void Pawn::setActive(bool active) { this->active = active; }

bool Pawn::isActive() { return active; }

void Pawn::onClick() {
  auto loop = EventLoop::getInstance();
  auto &teamManager = TeamManager::getInstance();

  auto &tm = TurnManager::getInstance();
  
  std::cout << "adsafasfdsfa  " << active << std::endl;
  if (context==TileContext::Finishing) {
    std::cout << "Finishing context" << std::endl;
  }
  if (!active && context == TileContext::Finishing) {
    std::cout << "adsafasfdsfa" << std::endl;
    return;
  }
  std::cout << "current player id : " << tm.getCurrentPlayerId()
            << " and team id is : " << teamId << std::endl;
  std::cout << "current dice value : " << tm.getCurrentRolledValue()
            << std::endl;
  if (teamId != tm.getCurrentPlayerId() || tm.getCurrentRolledValue() == 0) {
    // If someone decides to move someone else's pawn - he won't be able to do
    // that.
    return;
  }
  int value = tm.getCurrentRolledValue();
  cout << "ROLLED VALUE" << value << endl;
  cout << "Plyaer id  VALUE" << tm.getCurrentPlayerId() << endl;
  cout << "ID VALUE " << id << endl;
  tm.clearRoll();
  auto event = tm.getCurrentPlayerTurnEvent();
  std::cout << event << std::endl;
  event->completeTurn();
  std::cout << "moving with this value : " << value << std::endl;
  loop->pushEvent(
      std::make_shared<MovePawnEvent>(tm.getCurrentPlayerId(), id, value));
}

Color getDarkerShade(const Color &color, float factor = 0.9f) {
  // Clamp the factor between 0 and 1
  factor = std::max(0.0f, std::min(1.0f, factor));

  // Scale down each color component
  float red = color.getRedf() * factor;
  float green = color.getGreenf() * factor;
  float blue = color.getBluef() * factor;

  // Return the darker color
  return Color(red, green, blue);
}

Color getLighterShade(const Color &color, float factor = 1.1f) {
  // Ensure the factor is greater than 1 to lighten the color
  factor = std::max(1.0f, factor);

  // Scale up each color component, but clamp the values to a maximum of 1.0
  float red = std::min(1.0f, color.getRedf() * factor);
  float green = std::min(1.0f, color.getGreenf() * factor);
  float blue = std::min(1.0f, color.getBluef() * factor);

  // Return the lighter color
  return Color(red, green, blue);
}

void Pawn::renderSelf() const {
  auto &turnManager = TurnManager::getInstance();
  auto &drawer = MapDrawer::getInstance();
  const float cellSize = drawer.getCellSize();
  const float outerRadius = cellSize / 8;
  const float innerRadius = cellSize / 4;
  if (context == TileContext::Walkable || context == TileContext::Finishing) {

    Color red = Color(0.596f, 0.324f, 0.590f);
    drawer.drawCircle(drawer.getCellPosition(dimensions.x),
                      drawer.getCellPosition(dimensions.y),
                      drawer.getSizeOfCells(0.45f), color, 1000, black,
                      drawer.getSizeOfCells(0.05));
    if (turnManager.getCurrentPlayerId() == teamId && active && turnManager.getCurrentRolledValue() != 0) {
      auto &tm = TileManager::getInstance();
      auto currentTile = tm.findTileById(tileId);
      if (context == TileContext::Finishing && active) {
        drawer.drawStar(drawer.getCellPosition(dimensions.x) + cellSize / 2,
                        drawer.getCellPosition(dimensions.y) + cellSize / 2,
                        outerRadius, innerRadius, 5, white);
      } else if (context == TileContext::Walkable) {
        drawer.drawStar(drawer.getCellPosition(dimensions.x) + cellSize / 2,
                        drawer.getCellPosition(dimensions.y) + cellSize / 2,
                        outerRadius, innerRadius, 5, white);
      }
    }

  } else if (context == TileContext::Base) {
    auto &baseManager = BaseManager::getInstance();
    auto currentBase = baseManager.getBaseByTeamId(teamId);

    auto firstfreeSlot = currentBase->getFirstFreeSlot(this);

    bool res = currentBase->occupySlot(firstfreeSlot, this);

    auto inBaseCoords = currentBase->getSlotCoordinates(firstfreeSlot);
    auto newX = currentBase->getDimensions().x + inBaseCoords.first;
    auto newY = currentBase->getDimensions().y + inBaseCoords.second;
    drawer.drawCircle(drawer.getCellPosition(newX),
                      drawer.getCellPosition(newY),
                      drawer.getSizeOfCells(0.45f), color, 1000, black,
                      drawer.getSizeOfCells(0.05));
    setDimensions(Dimensions(newX, newY, drawer.getSizeOfCells(0.45),
                             drawer.getSizeOfCells(0.45)));
    if (turnManager.getCurrentPlayerId() == teamId &&
        turnManager.getCurrentRolledValue() == 6) {
      drawer.drawStar(drawer.getCellPosition(dimensions.x) + cellSize / 2,
                      drawer.getCellPosition(dimensions.y) + cellSize / 2,
                      outerRadius, innerRadius, 5, white);
    }

  }
  return;
}

void Pawn::setContext(TileContext c) { context = c; }

void Pawn::setDimensions(Dimensions d) const { dimensions = d; }

TileContext Pawn::getContext() { return context; }
