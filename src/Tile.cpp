#include "Tile.hpp"
#include "MapDrawer.hpp"
#include <GLFW/glfw3.h>
#include <string>

Color gray = Color(0.9f, 0.9f, 0.9f);
Color white = Color(1.0f, 1.0f, 1.0f);
void Tile::renderSelf() const {
  auto drawer = MapDrawer::getInstance();
  const float cellSize = drawer.getCellSize();
  /*drawer.drawCells();*/
  drawer.drawRectangle(dimensions.x, dimensions.y, cellSize, cellSize, white,
                       FILLED_WITH_STROKE, gray, 2.0);

  return;
}

std::string Tile::toString() {
  std::ostringstream oss;

  oss << "Tile [ID: " << id << ", Position: " << position << ", Color: ("
      << color.getRed() << ", " << color.getGreen() << ", " << color.getBlue()
      << ")"
      << ", Dimensions: (Width: " << dimensions.dx
      << ", Height: " << dimensions.dy << ", Depth: " << dimensions.dz << ")]";

  return oss.str();
}
