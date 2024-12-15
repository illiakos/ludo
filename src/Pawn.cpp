#include "Pawn.hpp"
#include "MapDrawer.hpp"
#include <GLFW/glfw3.h>
#include <cmath>

using namespace std;

const int RENDER_PRECISION = 1000;

const double PI = 3.141592653589793;

void Pawn::renderSelf() const {
  
    glColor3f(color.getRedf(), color.getGreenf(), color.getBluef()); // Set color
    glBegin(GL_TRIANGLE_FAN);                                        // Begin drawing a filled circle
    auto drawer = MapDrawer::getInstance();
    float halfCellSize = drawer.getSizeOfCells(1) / 2;
    // Center of the circle
    glVertex2f(dimensions.x + halfCellSize, dimensions.y + halfCellSize);
    auto segments = RENDER_PRECISION;
    // Draw the circle by approximating it with triangles
    for (int i = 0; i <= segments; i++)
    {
        float angle = 2.0f * PI * i / segments; // Angle in radians
        float x = dimensions.dx * cos(angle);
        float y = dimensions.dx * sin(angle);
        glVertex2f(dimensions.x + x + halfCellSize, dimensions.y + y + halfCellSize);
    }

    glEnd(); // End drawing
  return;
}
