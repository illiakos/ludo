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
  tm.clearRoll(); 
  std::cout << "moving with this value : " << value << std::endl;
  loop.enqueueEvent(std::make_shared<MovePawnEvent>(tm.getCurrentPlayerId(), id, value));
  

}

void Pawn::renderSelf() const {

  auto &drawer = MapDrawer::getInstance();
  if (context == TileContext::Walkable || context == TileContext::Finishing) {

    /*glColor3f (color.getRedf (), color.getGreenf (),*/
    /*    color.getBluef ());    // Set color*/
    /*glBegin (GL_TRIANGLE_FAN); // Begin drawing a filled circle*/
    /*float halfCellSize = drawer.getSizeOfCells (1) / 2;*/
    /*// Center of the circle*/
    /*glVertex2f (dimensions.x + halfCellSize, dimensions.y + halfCellSize);*/
    /*auto segments = RENDER_PRECISION;*/
    /*// Draw the circle by approximating it with triangles*/
    /*for (int i = 0; i <= segments; i++) {*/
    /*  float angle = 2.0f * PI * i / segments; // Angle in radians*/
    /*  float x = dimensions.dx * cos (angle);*/
    /*  float y = dimensions.dx * sin (angle);*/
    /*  glVertex2f (dimensions.x + x + halfCellSize, dimensions.y + y +
     * halfCellSize);*/
    /*}*/
    /**/
    /*glEnd (); // End drawing*/

    Color red = Color(0.596f, 0.324f, 0.590f);
    drawer.drawCircle(drawer.getCellPosition(dimensions.x),
                      drawer.getCellPosition(dimensions.y),
                      drawer.getSizeOfCells(0.45), red, 10000);

  } else if (context == TileContext::Base) {
    auto &baseManager = BaseManager::getInstance();
    auto currentBase = baseManager.getBaseByTeamId(teamId);

    Color red = Color(0.596f, 0.324f, 0.590f);

    auto inBaseCoords =
        currentBase->getSlotCoordinates(currentBase->getFirstFreeSlot());
    cout << drawer.getSizeOfCells(2) << endl;
    drawer.drawCircle(
        drawer.getCellPosition(currentBase->getDimensions().x +
                               inBaseCoords.first),
        drawer.getCellPosition(getDimensions().y + inBaseCoords.second),
        drawer.getSizeOfCells(0.45), red, 10000);
    currentBase->occupySlot(currentBase->getFirstFreeSlot());
  }

  return;
}

void Pawn::setContext(TileContext c) { context = c; }

void Pawn::setDimensions(Dimensions d) { dimensions = d; }

TileContext Pawn::getContext() { return context; }
