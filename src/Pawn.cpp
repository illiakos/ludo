#include "Pawn.hpp"
#include "BaseManager.hpp"
#include "EventLoop.hpp"
#include "MapDrawer.hpp"
#include "MovePawnEvent.hpp"
#include "TeamManager.hpp"
#include "TileContext.hpp"
#include "TurnManager.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <memory>
#include <ostream>

using namespace std;

const int RENDER_PRECISION = 1000;

const double PI = 3.141592653589793;

void Pawn::setActive(bool active) { active = active; }

bool Pawn::isActive() { return active; }

void Pawn::onClick() {
  std::cout << "pawn click ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;" << endl;

  auto& loop = EventLoop::getInstance();  
  auto& teamManager = TeamManager::getInstance();


  /*if (true) {*/
  /*  return;*/
  /*}*/


  auto& tm = TurnManager::getInstance();
  std::cout << "current player id : " << tm.getCurrentPlayerId() << " and team id is : " << teamId << std::endl;
  std::cout << "current dice value : " << tm.getCurrentRolledValue() << std::endl ;
  if (teamId != tm.getCurrentPlayerId() || tm.getCurrentRolledValue() == 0) {
    // If dolboyob decides to move someone else's pawn - he goes do pizdy
    return;
  }
  int value = tm.getCurrentRolledValue();
  cout << "ROLLED VALUE" << value << endl;
  cout << "Plyaer id  VALUE" << tm.getCurrentPlayerId() << endl;
  cout << "ID VALUE" << id << endl;
  tm.clearRoll(); 
  std::cout << "moving with this value : " << value << std::endl;
  loop.enqueueEvent(std::make_shared<MovePawnEvent>(tm.getCurrentPlayerId(), id, value));
  
  
}

void Pawn::renderSelf() const {

  auto &drawer = MapDrawer::getInstance();
  if (context == TileContext::Walkable || context == TileContext::Finishing) {

    Color red = Color(0.596f, 0.324f, 0.590f);
    cout << dimensions.x << dimensions.y << endl;
    drawer.drawCircle(drawer.getCellPosition(dimensions.x),
                      drawer.getCellPosition(dimensions.y),
                      drawer.getSizeOfCells(0.45), red, 10000);

  } else if (context == TileContext::Base) {
    auto &baseManager = BaseManager::getInstance();
    auto currentBase = baseManager.getBaseByTeamId(teamId);

    Color red = Color(0.596f, 0.324f, 0.590f);
    auto firstfreeSlot = currentBase->getFirstFreeSlot(this);

    bool res = currentBase->occupySlot(firstfreeSlot, this);

    auto inBaseCoords =
        currentBase->getSlotCoordinates(firstfreeSlot);
    cout << drawer.getSizeOfCells(2) << endl;
    auto newX = currentBase->getDimensions().x + inBaseCoords.first;
    auto newY = currentBase->getDimensions().y + inBaseCoords.second;
    drawer.drawCircle(
        drawer.getCellPosition(newX),
        drawer.getCellPosition(newY),
        drawer.getSizeOfCells(0.45), color, 10000);
    setDimensions(Dimensions(newX, newY , drawer.getSizeOfCells(0.45), drawer.getSizeOfCells(0.45)));
  }
  if (teamId == 1) {
    std::cout << "Red pawn coordinates: x = " << dimensions.x << " ; y = " << dimensions.y << " ;" << endl; 
  }
  return;
}

void Pawn::setContext(TileContext c) { context = c; }

void Pawn::setDimensions(Dimensions d) const { dimensions = d; }

TileContext Pawn::getContext() { return context; }
