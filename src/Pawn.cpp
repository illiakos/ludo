#include "Pawn.hpp"
#include "BaseManager.hpp"
#include "MapDrawer.hpp"
#include "TileContext.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <ostream>

using namespace std;

const int RENDER_PRECISION = 1000;

const double PI = 3.141592653589793;

void Pawn::renderSelf () const {

  auto &drawer = MapDrawer::getInstance ();
  if (context == TileContext::Walkable) {

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
    /*  glVertex2f (dimensions.x + x + halfCellSize, dimensions.y + y + halfCellSize);*/
    /*}*/
    /**/
    /*glEnd (); // End drawing*/

    Color red = Color (0.596f, 0.324f, 0.590f);
    drawer.drawCircle(drawer.getCellPosition(dimensions.x),drawer.getCellPosition(dimensions.y), drawer.getSizeOfCells(0.45), red, 10000);

  } else if (context == TileContext::Base) {
    auto &baseManager = BaseManager::getInstance ();
    auto currentBase = baseManager.getBaseByTeamId (teamId);

    Color red = Color (0.596f, 0.324f, 0.590f);

    auto inBaseCoords = currentBase->getSlotCoordinates (currentBase->getFirstFreeSlot ());
    std::cout << inBaseCoords.first << "|" << inBaseCoords.second << endl;
    cout << drawer.getSizeOfCells (2) << endl;
    drawer.drawCircle (
        drawer.getCellPosition (currentBase->getDimensions ().x + inBaseCoords.first),
        drawer.getCellPosition (getDimensions ().y + inBaseCoords.second),
        drawer.getSizeOfCells (0.45),
        red,
        10000);
    currentBase->occupySlot (currentBase->getFirstFreeSlot ());
  }

  return;
}

void Pawn::setContext (TileContext c) {
  context = c;
}

void Pawn::setDimensions (Dimensions d) {
  dimensions = d;
}

TileContext Pawn::getContext () {
  return context;
}
