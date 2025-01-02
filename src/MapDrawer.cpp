#include "MapDrawer.hpp"

#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>
#include <memory>
#include <ostream>
#include <thread>

#include "Color.hpp"
#include "ColorConstants.hpp"
#include "Renderable.hpp"
#include "WindowManager.hpp"

using namespace std;

const double PI = 3.141592653589793;

/*void MapDrawer::addRenderable(std::shared_ptr<Renderable> r) {*/
/*  renderableItems.push_back(r);*/
/*}*/

MapDrawer &MapDrawer::getInstance() {
  static MapDrawer instance(800, 15); // Single instance
  return instance;
}

float MapDrawer::getSizeOfCells(float cellsNumber) {
  auto cellSizeOpenGL = getCellSize();
  return cellSizeOpenGL * cellsNumber;
}

// Returns the size of a single cell
float MapDrawer::getCellSize() {
  auto windowSize = WindowManager::getInstance().getWindowSize().first;

  float conversionFactor = 2.0f / windowSize;

  float cellSizePixels =
      static_cast<float>(windowSize) / mapSize; // ~47.0588 pixels
  float cellSizeOpenGL =
      cellSizePixels * conversionFactor; // ~0.117647 OpenGL units
  return cellSizeOpenGL;
}

// Returns the OpenGL coordinate for a specific cell index
// From 0 to 14
float MapDrawer::getCellPosition(float cellIndex) {
  float cellSizeOpenGL = getSizeOfCells(1);

  // Calculate position for the given cell index
  return -1.0f + (cellIndex * cellSizeOpenGL);
}

MapDrawer::MapDrawer(int windowSize, int mapSize)
    : windowSize(windowSize), mapSize(mapSize) {}

// Function to draw a rectangle with a given color
void MapDrawer::drawRectangle(float x, float y, float width, float height,
                              const Color &fillColor, RectangleMode mode,
                              const Color &strokeColor, float borderWidth) {
  if (mode == FILLED || mode == FILLED_WITH_STROKE) {
    // Draw filled rectangle
    glColor3f(fillColor.getRedf(), fillColor.getGreenf(), fillColor.getBluef());
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
  }

  if (mode == STROKED || mode == FILLED_WITH_STROKE) {
    // Draw rectangle border (stroke)
    glLineWidth(borderWidth); // Set line thickness
    glColor3f(strokeColor.getRedf(), strokeColor.getGreenf(),
              strokeColor.getBluef());
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
  }
}

void MapDrawer::drawCircle(float cx, float cy, float radius, const Color &color,
                           int segments = 1000) {
  glColor3f(color.getRedf(), color.getGreenf(), color.getBluef()); // Set color
  glBegin(GL_TRIANGLE_FAN); // Begin drawing a filled circle

  float halfCellSize = getSizeOfCells(1) / 2;
  // Center of the circle
  glVertex2f(cx + halfCellSize, cy + halfCellSize);

  // Draw the circle by approximating it with triangles
  for (int i = 0; i <= segments; i++) {
    float angle = 2.0f * PI * i / segments; // Angle in radians
    float x = radius * cos(angle);
    float y = radius * sin(angle);
    glVertex2f(cx + x + halfCellSize, cy + y + halfCellSize);
  }

  glEnd(); // End drawing
}

void MapDrawer::drawTriangle(float x1, float y1, float x2, float y2, float x3,
                             float y3, const Color &color) {
  glColor3f(color.getRedf(), color.getGreenf(), color.getBluef()); // Set color
  glBegin(GL_TRIANGLES); // Begin drawing a triangle
  glVertex2f(x1, y1);    // First vertex
  glVertex2f(x2, y2);    // Second vertex
  glVertex2f(x3, y3);    // Third vertex
  glEnd();               // End drawing
}

void MapDrawer::drawStar(float cx, float cy, float outerRadius,
                         float innerRadius, int numPoints, const Color color) {
  if (numPoints < 5) {
    std::cerr << "Star must have at least 5 points.\n";
    return;
  }

  glColor3f(color.getRedf(), color.getGreenf(), color.getBluef()); // Set color
  glBegin(GL_TRIANGLE_FAN); // Use a triangle fan for the star

  float angleStep = M_PI / numPoints; // Step between outer and inner points
                                      // (half angle between star points)
  float angle = -M_PI_2; // Start angle (-90 degrees to orient the star upwards)

  // Draw the center of the star
  glVertex2f(cx, cy);

  for (int i = 0; i <= numPoints * 2; i++) {
    // Alternate between outer and inner radii
    float radius = (i % 2 == 0) ? outerRadius : innerRadius;

    // Calculate the vertex coordinates
    float x = cx + radius * cos(angle);
    float y = cy + radius * sin(angle);

    glVertex2f(x, y);

    // Increment the angle
    angle += angleStep;
  }

  glEnd(); // End drawing
}

void MapDrawer::drawArrow(float xStart, float yStart, float xEnd, float yEnd,
                          float headLength, float headWidth,
                          const Color &color) {
  // Set the arrow color
  glColor3f(color.getRedf(), color.getGreenf(), color.getBluef());

  // Calculate the direction vector of the arrow
  float dx = xEnd - xStart;
  float dy = yEnd - yStart;
  float length = sqrt(dx * dx + dy * dy);

  // Normalize the direction vector
  float dirX = dx / length;
  float dirY = dy / length;

  // Perpendicular vector for arrowhead
  float perpX = -dirY;
  float perpY = dirX;

  // Calculate the arrowhead points
  float arrowBaseX = xEnd - headLength * dirX;
  float arrowBaseY = yEnd - headLength * dirY;

  float arrowLeftX = arrowBaseX + headWidth * perpX / 2.0f;
  float arrowLeftY = arrowBaseY + headWidth * perpY / 2.0f;

  float arrowRightX = arrowBaseX - headWidth * perpX / 2.0f;
  float arrowRightY = arrowBaseY - headWidth * perpY / 2.0f;

  // Draw the arrow shaft
  glBegin(GL_LINES);
  glVertex2f(xStart, yStart);
  glVertex2f(arrowBaseX, arrowBaseY);
  glEnd();

  // Draw the arrowhead
  glBegin(GL_TRIANGLES);
  glVertex2f(xEnd, yEnd);               // Tip of the arrowhead
  glVertex2f(arrowLeftX, arrowLeftY);   // Left side of the arrowhead
  glVertex2f(arrowRightX, arrowRightY); // Right side of the arrowhead
  glEnd();
}

void MapDrawer::drawBase(float x, float y, const Color &color) {
  // Draw colored bg
  drawRectangle(getCellPosition(x), getCellPosition(y), getSizeOfCells(6),
                getSizeOfCells(6),
                color); // Blue color

  // Draw white part
  drawRectangle(getCellPosition(x + 1), getCellPosition(y + 1),
                getSizeOfCells(4), getSizeOfCells(4),
                white); // White color
  /*drawCircle(getCellPosition(x + 1.5), getCellPosition(y + 1.5),
   * getSizeOfCells(0.45), color);*/
  /*drawCircle(getCellPosition(x + 3.5), getCellPosition(y + 1.5),
   * getSizeOfCells(0.45), color);*/
  /*drawCircle(getCellPosition(x + 3.5), getCellPosition(y + 3.5),
   * getSizeOfCells(0.45), color);*/
  /*drawCircle(getCellPosition(x + 1.5), getCellPosition(y + 3.5),
   * getSizeOfCells(0.45), color);*/
}

void MapDrawer::drawRoads() {
  // Draw blue road
  drawRectangle(getCellPosition(6), getCellPosition(1), getSizeOfCells(1),
                getSizeOfCells(1), blue);
  drawRectangle(getCellPosition(7), getCellPosition(1), getSizeOfCells(1),
                getSizeOfCells(5), blue);

  // Draw red road
  drawRectangle(getCellPosition(1), getCellPosition(8), getSizeOfCells(1),
                getSizeOfCells(1), red);
  drawRectangle(getCellPosition(1), getCellPosition(7), getSizeOfCells(5),
                getSizeOfCells(1), red);

  // Draw green road
  drawRectangle(getCellPosition(8), getCellPosition(13), getSizeOfCells(1),
                getSizeOfCells(1), green);
  drawRectangle(getCellPosition(7), getCellPosition(9), getSizeOfCells(1),
                getSizeOfCells(5), green);

  // Draw yellow road
  drawRectangle(getCellPosition(13), getCellPosition(6), getSizeOfCells(1),
                getSizeOfCells(1), yellow);
  drawRectangle(getCellPosition(9), getCellPosition(7), getSizeOfCells(5),
                getSizeOfCells(1), yellow);
}

void MapDrawer::drawCells() {
  const float sizeOfCell = getSizeOfCells(1);
  for (int i = 0; i < mapSize; i++) {
    for (int j = 0; j < mapSize; j++) {
      drawRectangle(getCellPosition(i), getCellPosition(j), sizeOfCell,
                    sizeOfCell, white, FILLED_WITH_STROKE, gray, 2.0);
    }
  }
}

void MapDrawer::drawMiddle() {
  // Draw the center background (3x3 cells)
  drawRectangle(getCellPosition(6), getCellPosition(6), getSizeOfCells(3),
                getSizeOfCells(3), gray);

  // Shared variables
  float cellSize = getSizeOfCells(1);            // Single cell size
  float halfCell = cellSize / 2;                 // Half cell size
  float centerX = getCellPosition(7) + halfCell; // Center X position
  float centerY = getCellPosition(7) + halfCell; // Center Y position

  // Draw Red Triangle (bottom-left to center to top-left)
  drawTriangle(getCellPosition(6),
               getCellPosition(6), // Bottom-left corner
               centerX,
               centerY, // Center of the square
               getCellPosition(6),
               getCellPosition(8) +
                   cellSize, // Top-left (y3 shifted up by 1 cell)
               red);

  // Draw Blue Triangle (bottom-left to center to bottom-right)
  drawTriangle(getCellPosition(6),
               getCellPosition(6), // Bottom-left corner
               centerX,
               centerY, // Center of the square
               getCellPosition(8) + cellSize,
               getCellPosition(6), // Bottom-right (x3 shifted right by 1 cell)
               blue                // Blue color
  );

  // Draw Green Triangle (top-left to center to top-right)
  drawTriangle(
      getCellPosition(6),
      getCellPosition(8) + cellSize, // Top-left corner
      centerX,
      centerY, // Center of the square
      getCellPosition(8) + cellSize,
      getCellPosition(8) + cellSize, // Top-right (x3 shifted right by 1 cell)
      green                          // Green color
  );

  // Draw Yellow Triangle (bottom-right to center to top-right)
  drawTriangle(getCellPosition(8) + cellSize,
               getCellPosition(8) + cellSize, // Bottom-right corner
               centerX,
               centerY, // Center of the square
               getCellPosition(8) + cellSize,
               getCellPosition(6), // Top-right (y3 shifted up by 1 cell)
               yellow              // Yellow color
  );
}

void MapDrawer::drawLudoBoard() {
  /*drawCells();*/

  drawMiddle();

  // drawBase(0, 0, blue); // Blue

  // //drawBase(0, 9, red); // Red

  // drawBase(9, 9, green); // Green

  // drawBase(9, 0, yellow); // Yellow

  /*drawRoads();*/

  // Test circle
  drawCircle(getCellPosition(3), getCellPosition(6), getSizeOfCells(0.45),
             green);
}

void MapDrawer::enqueueRenderTask(std::function<void()> task) {
  {
    std::lock_guard<std::mutex> lock(queueMutex);
    taskQueue.push(task);
  }
  condition.notify_one();
}

void MapDrawer::drawMap() {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW!" << std::endl;
    return;
  }

  window =
      glfwCreateWindow(windowSize, windowSize, "GLFW Test Window", NULL, NULL);

  // Make the window's context current
  glfwMakeContextCurrent(window);

  // Main event loop
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    drawLudoBoard();
    // Draw persistent items
    {
      std::lock_guard<std::mutex> lock(queueMutex);
      for (const auto &item : renderableItems) {
        item->renderSelf();
      }
    }

    // Draw the Ludo board

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Clean up and exit
  glfwDestroyWindow(window);
  glfwTerminate();
}

void MapDrawer::log() {}
void MapDrawer::addRenderable(std::shared_ptr<Renderable> renderable) {
  std::lock_guard<std::mutex> lock(renderablesMutex);
  renderableItems.push_back(renderable);
}

void MapDrawer::removeRenderable(std::shared_ptr<Renderable> renderable) {
  std::lock_guard<std::mutex> lock(renderablesMutex);
  renderableItems.erase(
      std::remove(renderableItems.begin(), renderableItems.end(), renderable),
      renderableItems.end());
}
void MapDrawer::clearRenderables() {
  std::lock_guard<std::mutex> lock(renderablesMutex);
  renderableItems.clear();
}

// Helper function to check if two ranges overlap
bool doDimensionsOverlap(const Dimensions &dim1, const Dimensions &dim2) {
  // Check for overlap in the x-dimension
  bool xOverlap = !(dim1.x + dim1.dx <= dim2.x || dim2.x + dim2.dx <= dim1.x);

  // Check for overlap in the y-dimension
  bool yOverlap = !(dim1.y + dim1.dy <= dim2.y || dim2.y + dim2.dy <= dim1.y);

  return xOverlap && yOverlap;
}

// Helper function to log renderable information
void logRenderableInfo(const std::shared_ptr<Renderable> &renderable, float x,
                       float y, float dx, float dy) {
  if (renderable->getZIndex() == 2) {
    std::cout << "PAWN!!!! renderableDim: (" << x << ", " << y << ", " << dx
              << ", " << dy << ")\n";
  } else {
    std::cout << "Tile!!!! renderableDim: (" << x << ", " << y << ", " << dx
              << ", " << dy << ")\n";
  }
}

// Helper function to check if a click is on a circle
bool isClickOnCircle(float clickX, float clickY, float renderableXOpenGL,
                     float renderableYOpenGL, float cellSizeOpenGL) {
  float radius = cellSizeOpenGL * 0.45f;
  float centerX = renderableXOpenGL + cellSizeOpenGL / 2;
  float centerY = renderableYOpenGL + cellSizeOpenGL / 2;

  float distanceSquared = (clickX - centerX) * (clickX - centerX) +
                          (clickY - centerY) * (clickY - centerY);
  return distanceSquared <= radius * radius;
}

// Helper function to check if a click is on a rectangle
bool isClickOnRectangle(float clickX, float clickY, float minX, float minY,
                        float dx, float dy) {
  float maxX = minX + dx;
  float maxY = minY + dy;
  return clickX >= minX && clickX <= maxX && clickY >= minY && clickY <= maxY;
}

// Helper function to update the renderable with the highest zIndex
std::shared_ptr<Renderable> updateHighestZIndexRenderable(
    const std::shared_ptr<Renderable> &currentRenderable,
    std::shared_ptr<Renderable> &highestRenderable, int &maxZIndex) {
  int zIndex = currentRenderable->getZIndex();
  if (!highestRenderable || zIndex > maxZIndex) {
    highestRenderable = currentRenderable;
    maxZIndex = zIndex;
  }
  return highestRenderable;
}

std::shared_ptr<Renderable> MapDrawer::findByDimensionsRange(float clickX,
                                                             float clickY) {
  std::lock_guard<std::mutex> lock(
      renderablesMutex); // Lock renderables for thread safety

  // Calculate cell size in OpenGL units
  float cellSizeOpenGL = getCellSize();

  std::shared_ptr<Renderable> highestZIndexRenderable = nullptr;
  int maxZIndex = std::numeric_limits<int>::min();

  for (const auto &renderable : renderableItems) {
    if (!renderable)
      continue; // Skip null pointers

    // Get renderable dimensions and convert to OpenGL coordinates
    Dimensions renderableDim = renderable->getDimensions();
    float renderableXOpenGL = getCellPosition(renderableDim.x);
    float renderableYOpenGL = getCellPosition(renderableDim.y);
    float renderableDXOpenGL = getSizeOfCells(renderableDim.dx);
    float renderableDYOpenGL = getSizeOfCells(renderableDim.dy);

    // Debugging information
    logRenderableInfo(renderable, renderableXOpenGL, renderableYOpenGL,
                      renderableDXOpenGL, renderableDYOpenGL);

    // Handle renderable type
    if (renderable->getZIndex() == 2) { // Circle
      if (isClickOnCircle(clickX, clickY, renderableXOpenGL, renderableYOpenGL,
                          cellSizeOpenGL)) {
        highestZIndexRenderable = updateHighestZIndexRenderable(
            renderable, highestZIndexRenderable, maxZIndex);
      }
    } else if (renderable->getZIndex() == 1) { // Rectangle
      if (isClickOnRectangle(clickX, clickY, renderableXOpenGL,
                             renderableYOpenGL, renderableDXOpenGL,
                             renderableDYOpenGL)) {
        highestZIndexRenderable = updateHighestZIndexRenderable(
            renderable, highestZIndexRenderable, maxZIndex);
      }
    }
  }

  return highestZIndexRenderable; // Return the renderable with the highest
                                  // zIndex
}
