#include "MapDrawer.hpp"
#include "Color.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <memory>
#include "Renderable.hpp"
#include "WindowManager.hpp"

using namespace std;

Color blue = Color(0.004f, 0.725f, 0.945f);
Color white = Color(1.0f, 1.0f, 1.0f);
Color gray = Color(0.9f, 0.9f, 0.9f);
Color red = Color(0.996f, 0.180f, 0.090f);
Color green = Color(0.29f, 0.729f, 0.29f);
Color yellow = Color(1.0f, 0.784f, 0.208f);

const double PI = 3.141592653589793;

void MapDrawer::addRenderable(std::shared_ptr<Renderable> r) {
  renderableItems.push_back(r);
}

MapDrawer &MapDrawer::getInstance() {
    static MapDrawer instance; // Single instance
    return instance;
}

float MapDrawer::getSizeOfCells(float cellsNumber)
{
    auto cellSizeOpenGL = getCellSize();
    return cellSizeOpenGL * cellsNumber;
}

// Returns the size of a single cell
float MapDrawer::getCellSize() {

    auto windowSize = WindowManager::getInstance().getWindowSize().first;

    float conversionFactor = 2.0f / windowSize;
  
    float cellSizePixels = static_cast<float>(windowSize) / mapSize; // ~47.0588 pixels
    float cellSizeOpenGL = cellSizePixels * conversionFactor;        // ~0.117647 OpenGL units
    return cellSizeOpenGL;
}

// Returns the OpenGL coordinate for a specific cell index
// From 0 to 14
float MapDrawer::getCellPosition(float cellIndex)
{
    float cellSizeOpenGL = getSizeOfCells(1);

    // Calculate position for the given cell index
    return -1.0f + (cellIndex * cellSizeOpenGL);
}

MapDrawer::MapDrawer(int windowSize, int mapSize) : windowSize(windowSize), mapSize(mapSize) {}

// Function to draw a rectangle with a given color
void MapDrawer::drawRectangle(
    float x, float y, float width, float height,
    const Color &fillColor, RectangleMode mode,
    const Color &strokeColor, float borderWidth)
{

    if (mode == FILLED || mode == FILLED_WITH_STROKE)
    {
        // Draw filled rectangle
        glColor3f(fillColor.getRedf(), fillColor.getGreenf(), fillColor.getBluef());
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();
    }

    if (mode == STROKED || mode == FILLED_WITH_STROKE)
    {
        // Draw rectangle border (stroke)
        glLineWidth(borderWidth); // Set line thickness
        glColor3f(strokeColor.getRedf(), strokeColor.getGreenf(), strokeColor.getBluef());
        glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();
    }
}

void MapDrawer::drawCircle(float cx, float cy, float radius, const Color &color, int segments = 1000)
{
    glColor3f(color.getRedf(), color.getGreenf(), color.getBluef()); // Set color
    glBegin(GL_TRIANGLE_FAN);                                        // Begin drawing a filled circle

    float halfCellSize = getSizeOfCells(1) / 2;
    // Center of the circle
    glVertex2f(cx + halfCellSize, cy + halfCellSize);

    // Draw the circle by approximating it with triangles
    for (int i = 0; i <= segments; i++)
    {
        float angle = 2.0f * PI * i / segments; // Angle in radians
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(cx + x + halfCellSize, cy + y + halfCellSize);
    }

    glEnd(); // End drawing
}

void MapDrawer::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, const Color &color)
{
    glColor3f(color.getRedf(), color.getGreenf(), color.getBluef()); // Set color
    glBegin(GL_TRIANGLES);                                           // Begin drawing a triangle
    glVertex2f(x1, y1);                                              // First vertex
    glVertex2f(x2, y2);                                              // Second vertex
    glVertex2f(x3, y3);                                              // Third vertex
    glEnd();                                                         // End drawing
}

void MapDrawer::drawBase(float x, float y, const Color &color)
{
    // Draw colored bg
    drawRectangle(getCellPosition(x), getCellPosition(y), getSizeOfCells(6), getSizeOfCells(6), color); // Blue color

    // Draw white part
    drawRectangle(getCellPosition(x + 1), getCellPosition(y + 1), getSizeOfCells(4), getSizeOfCells(4), white); // White color
    drawCircle(getCellPosition(x + 1.5), getCellPosition(y + 1.5), getSizeOfCells(0.45), color);
    drawCircle(getCellPosition(x + 3.5), getCellPosition(y + 1.5), getSizeOfCells(0.45), color);
    drawCircle(getCellPosition(x + 3.5), getCellPosition(y + 3.5), getSizeOfCells(0.45), color);
    drawCircle(getCellPosition(x + 1.5), getCellPosition(y + 3.5), getSizeOfCells(0.45), color);
}

void MapDrawer::drawRoads()
{

    // Draw blue road
    drawRectangle(getCellPosition(6), getCellPosition(1), getSizeOfCells(1), getSizeOfCells(1), blue);
    drawRectangle(getCellPosition(7), getCellPosition(1), getSizeOfCells(1), getSizeOfCells(5), blue);

    // Draw red road
    drawRectangle(getCellPosition(1), getCellPosition(8), getSizeOfCells(1), getSizeOfCells(1), red);
    drawRectangle(getCellPosition(1), getCellPosition(7), getSizeOfCells(5), getSizeOfCells(1), red);

    // Draw green road
    drawRectangle(getCellPosition(8), getCellPosition(13), getSizeOfCells(1), getSizeOfCells(1), green);
    drawRectangle(getCellPosition(7), getCellPosition(9), getSizeOfCells(1), getSizeOfCells(5), green);

    // Draw yellow road
    drawRectangle(getCellPosition(13), getCellPosition(6), getSizeOfCells(1), getSizeOfCells(1), yellow);
    drawRectangle(getCellPosition(9), getCellPosition(7), getSizeOfCells(5), getSizeOfCells(1), yellow);
}

void MapDrawer::drawCells()
{
    const float sizeOfCell = getSizeOfCells(1);
    for (int i = 0; i < mapSize; i++)
    {
        for (int j = 0; j < mapSize; j++)
        {
            drawRectangle(getCellPosition(i), getCellPosition(j), sizeOfCell, sizeOfCell, white, FILLED_WITH_STROKE, gray, 2.0);
        }
    }
}

void MapDrawer::drawMiddle()
{
    // Draw the center background (3x3 cells)
    drawRectangle(getCellPosition(6), getCellPosition(6), getSizeOfCells(3), getSizeOfCells(3), gray);

    // Shared variables
    float cellSize = getSizeOfCells(1);            // Single cell size
    float halfCell = cellSize / 2;                 // Half cell size
    float centerX = getCellPosition(7) + halfCell; // Center X position
    float centerY = getCellPosition(7) + halfCell; // Center Y position

    // Draw Red Triangle (bottom-left to center to top-left)
    drawTriangle(
        getCellPosition(6), getCellPosition(6),            // Bottom-left corner
        centerX, centerY,                                  // Center of the square
        getCellPosition(6), getCellPosition(8) + cellSize, // Top-left (y3 shifted up by 1 cell)
        red);

    // Draw Blue Triangle (bottom-left to center to bottom-right)
    drawTriangle(
        getCellPosition(6), getCellPosition(6),            // Bottom-left corner
        centerX, centerY,                                  // Center of the square
        getCellPosition(8) + cellSize, getCellPosition(6), // Bottom-right (x3 shifted right by 1 cell)
        blue                                               // Blue color
    );

    // Draw Green Triangle (top-left to center to top-right)
    drawTriangle(
        getCellPosition(6), getCellPosition(8) + cellSize,            // Top-left corner
        centerX, centerY,                                             // Center of the square
        getCellPosition(8) + cellSize, getCellPosition(8) + cellSize, // Top-right (x3 shifted right by 1 cell)
        green                                                         // Green color
    );

    // Draw Yellow Triangle (bottom-right to center to top-right)
    drawTriangle(
        getCellPosition(8) + cellSize, getCellPosition(8) + cellSize, // Bottom-right corner
        centerX, centerY,                                             // Center of the square
        getCellPosition(8) + cellSize, getCellPosition(6),            // Top-right (y3 shifted up by 1 cell)
        yellow                                                        // Yellow color
    );
}

void MapDrawer::drawLudoBoard()
{
    
    drawCells();

    drawMiddle();

    drawBase(0, 0, blue); // Blue

    drawBase(0, 9, red); // Red

    drawBase(9, 9, green); // Green

    drawBase(9, 0, yellow); // Yellow

    drawRoads();

    // Test circle
    drawCircle(getCellPosition(3), getCellPosition(6), getSizeOfCells(0.45), green);
}

void MapDrawer::drawMap()
{
    cout << "DRAWING WINDOW" << endl;
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return;
    }

    GLFWwindow *window = glfwCreateWindow(windowSize, windowSize, "GLFW Test Window", NULL, NULL);

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Main event loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the Ludo board
        drawLudoBoard();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up and exit
    glfwDestroyWindow(window);
    glfwTerminate();
}
