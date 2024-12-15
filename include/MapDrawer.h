#ifndef MAP_DRAWER_H
#define MAP_DRAWER_H
#include "Color.h"

using namespace std;

enum RectangleMode {
    FILLED,            // Filled rectangle only
    STROKED,           // Only border (stroke)
    FILLED_WITH_STROKE // Filled rectangle with a border
};

class MapDrawer {
    public:
    MapDrawer(int windowSize, int mapSize);
    void drawMap();
    private:
    int windowSize;
    int mapSize;
    float getCellPosition(float cellIndex);
    float getSizeOfCells(float cellsNumber);
    void drawRectangle(
        float x, float y, float width, float height, 
        const Color &fillColor, RectangleMode mode = FILLED, 
        const Color &strokeColor = Color(0, 0, 0), float borderWidth = 1.0f
    );
    void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, const Color &color);
    void drawCircle(float cx, float cy, float radius, const Color &color, int segments);
    void drawLudoBoard();
    void drawRoads();
    void drawCells();
    void drawBase(float x, float y, const Color &color);
    void drawMiddle();
};

#endif