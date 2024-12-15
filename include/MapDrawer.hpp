#ifndef MAP_DRAWER_H
#define MAP_DRAWER_H
#include "Color.hpp"
#include "Renderable.hpp"
#include <memory>
#include <vector>

using namespace std;

enum RectangleMode {
  FILLED,            // Filled rectangle only
  STROKED,           // Only border (stroke)
  FILLED_WITH_STROKE // Filled rectangle with a border
};



class MapDrawer : public RenderableContainer {

public:
  void drawMap();
  
  float getCellPosition(float cellIndex);
  static MapDrawer &getInstance();
  float getSizeOfCells(float cellsNumber);
  float getCellSize();

  void drawRectangle(float x, float y, float width, float height,
                     const Color &fillColor, RectangleMode mode = FILLED,
                     const Color &strokeColor = Color(0, 0, 0),
                     float borderWidth = 1.0f);
  void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3,
                    const Color &color);
  void drawCircle(float cx, float cy, float radius, const Color &color,
                  int segments);
  void drawLudoBoard();
  void drawRoads();
  void drawCells();
  void drawBase(float x, float y, const Color &color);
  void drawMiddle();
  void drawPawn();
  void addRenderable(std::shared_ptr<Renderable> r) override;
private:
  MapDrawer() = default;
  MapDrawer(int windowSize, int mapSize);

  std::vector<std::shared_ptr<Renderable>> renderableItems;

  int windowSize;
  int mapSize;
};

#endif
