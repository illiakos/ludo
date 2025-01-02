#include "Dimensions.hpp"
#include "MapDrawer.hpp"
#include <iostream>

// Converts grid coordinates (0-15) to OpenGL coordinates
std::pair<float, float>
Dimensions::gridToOpenGL(int x, int y, const Dimensions &gridDimensions) {

  auto &drawer = MapDrawer::getInstance();
  // Get cell size in OpenGL units
  float cellSizeOpenGL = drawer.getCellPosition(1) - drawer.getCellPosition(0);

  // Calculate OpenGL position for x and y
  float oglX = drawer.getCellPosition(x);
  float oglY = drawer.getCellPosition(y);

  return {oglX, oglY};
}