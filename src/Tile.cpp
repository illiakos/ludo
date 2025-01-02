#include "Tile.hpp"

#include <GLFW/glfw3.h>

#include <string>

#include "ColorConstants.hpp"
#include "MapDrawer.hpp"
#include "TileContext.hpp"

void Tile::renderSelf() const {
  auto &drawer = MapDrawer::getInstance();
  const float cellSize = drawer.getCellSize();
  /*drawer.drawCells();*/
  drawer.drawRectangle(drawer.getCellPosition(dimensions.x),
                       drawer.getCellPosition(dimensions.y), cellSize, cellSize,
                       white, FILLED_WITH_STROKE, gray, 2.0);

  return;
}

std::string contextToString(TileContext context) {
  switch (context) {
  case TileContext::Walkable:

    return "Walkable";
  case TileContext::Base:
    return "Base";
  case TileContext::Finishing:
    return "Finishing";
  }
  return "";
}

std::string Tile::toString() {
  std::ostringstream oss;

  oss << "Tile [ID: " << id << ", Position: " << position << ", Color: ("
      << color.getRed() << ", " << color.getGreen() << ", " << color.getBlue()
      << ")"
      << ", Dimensions: (Width: " << dimensions.dx << "| "
      << contextToString(context) << " | " << ", Height: " << dimensions.dy
      << ", Depth: " << dimensions.dz << ")]";

  return oss.str();
}

int Tile::getPosition() const { return position; }

int Tile::getId() const { return id; }

TileContext Tile::getContext() { return context; }

// Helper to convert context to string
std::string Tile::contextToString(TileContext context) const {
  switch (context) {
  case TileContext::Base:
    return "Base";
  case TileContext::Walkable:
    return "Walkable";
  case TileContext::Finishing:
    return "Finishing";
  default:
    return "Unknown";
  }
}
