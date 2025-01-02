#include "Base.hpp"
#include "BaseManager.hpp"
#include "Board.hpp"
#include "Color.hpp"
#include "EventDispatcher.hpp"
#include "EventLoop.hpp"
#include "MovePawnEvent.hpp"
#include "MovePawnHandler.hpp"
#include "Player.hpp"
#include "PlayerTurnEvent.hpp"
#include "PlayerTurnHandler.hpp"
#include "RollDiceHandler.hpp"
#include "SpecialTiles.hpp"
#include "StopGameEvent.hpp"
#include "StopGameHandler.hpp"
#include "Team.hpp"
#include "TeamManager.hpp"
#include "TileContext.hpp"
#include "TileManager.hpp"
#include "TurnManager.hpp"
#include "ClickHandler.hpp"
#include "WindowManager.hpp"
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include <iostream>
#include <memory>
#include <ostream>
#include FT_FREETYPE_H
#define STB_IMAGE_IMPLEMENTATION
#include "MapDrawer.hpp"
#include "stb_image.h"
#include <thread>

void testGLFW () {
  if (!glfwInit ()) {
    std::cerr << "Failed to initialize GLFW!" << std::endl;
    exit (EXIT_FAILURE);
  }

  GLFWwindow *window = glfwCreateWindow (800, 600, "GLFW Test Window", NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create GLFW window!" << std::endl;
    glfwTerminate ();
    exit (EXIT_FAILURE);
  }

  glfwMakeContextCurrent (window);
  std::cout << "GLFW initialized successfully!" << std::endl;

  // Close immediately for testing
  glfwDestroyWindow (window);
  glfwTerminate ();
}

// Function to test FreeType
void testFreeType () {
  FT_Library ft;
  if (FT_Init_FreeType (&ft)) {
    std::cerr << "Failed to initialize FreeType!" << std::endl;
    exit (EXIT_FAILURE);
  }

  // Load a font file (use any TTF file you have)
  FT_Face face;
  if (FT_New_Face (ft, "../src/assets/fonts/OpenSans-Regular.ttf", 0, &face)) {
    std::cerr << "Failed to load font!" << std::endl;
    FT_Done_FreeType (ft);
    exit (EXIT_FAILURE);
  }

  std::cout << "FreeType initialized and font loaded successfully!" << std::endl;

  // Cleanup
  FT_Done_Face (face);
  FT_Done_FreeType (ft);
}

// Function to test stb_image
void testStbImage () {
  int width, height, channels;
  unsigned char *data = stbi_load ("../src/assets/images/test.jpg", &width, &height, &channels, 0);
  if (!data) {
    std::cerr << "Failed to load image with stb_image!" << std::endl;
    exit (EXIT_FAILURE);
  }

  std::cout << "Image loaded successfully with stb_image! Dimensions: " << width << "x" << height
            << ", Channels: " << channels << std::endl;

  stbi_image_free (data);
}

void initializeTiles () {

  Color blue = Color (0.004f, 0.725f, 0.945f);
  Color red = Color (0.996f, 0.180f, 0.090f);
  Color green = Color (0.29f, 0.729f, 0.29f);
  Color yellow = Color (1.0f, 0.784f, 0.208f);

  TileManager &tileManager = TileManager::getInstance ();
  MapDrawer &mapDrawer = MapDrawer::getInstance ();

  // Walkable tiles (updated based on new coordinates)
  int position = 2;
  for (int x = 2; x <= 5; x++) {
    auto walkableTile = std::make_shared<Tile> (
        Dimensions (x, 8, 1, 1), position, position, Color (0.8f, 0.8f, 0.8f), TileContext::Walkable);
    tileManager.addTile (walkableTile);
    mapDrawer.addRenderable (walkableTile);
    position++;
  }

  for (int y = 9; y <= 15; y++) {
    // Skip safe tile
    if (y == 12) {
      position++;
      continue;
    }
    auto walkableTile = std::make_shared<Tile> (
        Dimensions (6, y, 1, 1), position, position, Color (0.8f, 0.8f, 0.8f), TileContext::Walkable);
    tileManager.addTile (walkableTile);
    mapDrawer.addRenderable (walkableTile);
    position++;
  }

  position++; // Skip green transition position
  auto walkableTile = std::make_shared<Tile> (
      Dimensions (8, 14, 1, 1), position, position, Color (0.8f, 0.8f, 0.8f), TileContext::Walkable);
  tileManager.addTile (walkableTile);
  mapDrawer.addRenderable (walkableTile);
  position++; // Skip green start position

  for (int y = 12; y >= 9; y--) {
    auto walkableTile = std::make_shared<Tile> (
        Dimensions (8, y, 1, 1), position, position, Color (0.8f, 0.8f, 0.8f), TileContext::Walkable);
    tileManager.addTile (walkableTile);
    mapDrawer.addRenderable (walkableTile);
    position++;
  }

  cout << "ABOBA" << position << endl;
  for (int x = 9; x <= 14; x++) {
    // Skip safe tile
    if (x == 12) {
      position++;
      continue;
    }
    auto walkableTile = std::make_shared<Tile> (
        Dimensions (x, 8, 1, 1), position, position, Color (0.8f, 0.8f, 0.8f), TileContext::Walkable);
    tileManager.addTile (walkableTile);
    mapDrawer.addRenderable (walkableTile);
    position++;
  }

  position++; // Skip yellow transition position
  walkableTile = std::make_shared<Tile> (
      Dimensions (14, 6, 1, 1), position, position, Color (0.8f, 0.8f, 0.8f), TileContext::Walkable);
  tileManager.addTile (walkableTile);
  mapDrawer.addRenderable (walkableTile);
  position++;
  position++; // Skip yellow transition position

  for (int x = 12; x >= 9; x--) {
    auto walkableTile = std::make_shared<Tile> (
        Dimensions (x, 6, 1, 1), position, position, Color (0.8f, 0.8f, 0.8f), TileContext::Walkable);
    tileManager.addTile (walkableTile);
    mapDrawer.addRenderable (walkableTile);
    position++;
  }

  for (int y = 5; y >= 0; y--) {
    // Skip safe tile
    if (y == 2) {
      position++;
      continue;
    }
    auto walkableTile = std::make_shared<Tile> (
        Dimensions (8, y, 1, 1), position, position, Color (0.8f, 0.8f, 0.8f), TileContext::Walkable);
    tileManager.addTile (walkableTile);
    mapDrawer.addRenderable (walkableTile);
    position++;
  }

  position++; // Skip blue transition position
  walkableTile = std::make_shared<Tile> (
      Dimensions (6, 0, 1, 1), position, position, Color (0.8f, 0.8f, 0.8f), TileContext::Walkable);
  tileManager.addTile (walkableTile);
  mapDrawer.addRenderable (walkableTile);
  position++;
  position++; // Skip blue transition position

  for (int y = 2; y <= 5; y++) {
    auto walkableTile = std::make_shared<Tile> (
        Dimensions (6, y, 1, 1), position, position, Color (0.8f, 0.8f, 0.8f));
    tileManager.addTile (walkableTile);
    mapDrawer.addRenderable (walkableTile);
    position++;
  }

  for (int x = 5; x >= 0; x--) {
    // Skip safe tile
    if (x == 2) {
      position++;
      continue;
    }
    auto walkableTile = std::make_shared<Tile> (
        Dimensions (x, 6, 1, 1), position, position, Color (0.8f, 0.8f, 0.8f));
    tileManager.addTile (walkableTile);
    mapDrawer.addRenderable (walkableTile);
    position++;
  }

  position++; // Skip red transition position
  walkableTile = std::make_shared<Tile> (
      Dimensions (0, 8, 1, 1), position, position, Color (0.8f, 0.8f, 0.8f));
  tileManager.addTile (walkableTile);
  mapDrawer.addRenderable (walkableTile);

  // Safe tiles
  auto redSafe = std::make_shared<SafeTile> (Dimensions (6, 12, 1, 1), 9, 9, red);
  auto blueSafe = std::make_shared<SafeTile> (Dimensions (2, 6, 1, 1), 48, 48, blue);
  auto greenSafe = std::make_shared<SafeTile> (Dimensions (12, 8, 1, 1), 22, 22, green);
  auto yellowSafe = std::make_shared<SafeTile> (Dimensions (8, 2, 1, 1), 35, 35, yellow);

  tileManager.addTile (redSafe);
  tileManager.addTile (blueSafe);
  tileManager.addTile (greenSafe);
  tileManager.addTile (yellowSafe);

  mapDrawer.addRenderable (redSafe);
  mapDrawer.addRenderable (blueSafe);
  mapDrawer.addRenderable (greenSafe);
  mapDrawer.addRenderable (yellowSafe);

  // Transition tiles
  auto redTransition = std::make_shared<TransitionTile> (
      Dimensions (0, 7, 1, 1), 51, 51, 1, 1, Color (0.8f, 0.8f, 0.8f));
  auto blueTransition = std::make_shared<TransitionTile> (
      Dimensions (7, 0, 1, 1), 38, 38, 2, 2, Color (0.8f, 0.8f, 0.8f));
  auto greenTransition = std::make_shared<TransitionTile> (
      Dimensions (7, 14, 1, 1), 12, 12, 3, 3, Color (0.8f, 0.8f, 0.8f));
  auto yellowTransition = std::make_shared<TransitionTile> (
      Dimensions (14, 7, 1, 1), 25, 25, 4, 4, Color (0.8f, 0.8f, 0.8f));

  tileManager.addTile (redTransition);
  tileManager.addTile (blueTransition);
  tileManager.addTile (greenTransition);
  tileManager.addTile (yellowTransition);

  mapDrawer.addRenderable (redTransition);
  mapDrawer.addRenderable (blueTransition);
  mapDrawer.addRenderable (greenTransition);
  mapDrawer.addRenderable (yellowTransition);

  // Starting tiles for each team (corrected positions)
  auto redStart = std::make_shared<StartingTile> (Dimensions (1, 8, 1, 1), 1, 1, red, 1);
  auto blueStart = std::make_shared<StartingTile> (Dimensions (6, 1, 1, 1), 13, 13, blue, 3);
  auto greenStart = std::make_shared<StartingTile> (Dimensions (8, 13, 1, 1), 40, 40, green, 4);
  auto yellowStart = std::make_shared<StartingTile> (Dimensions (13, 6, 1, 1), 27, 27, yellow, 2);

  // Adding starting tiles to the manager and rendering
  tileManager.addTile (redStart);
  tileManager.addTile (blueStart);
  tileManager.addTile (greenStart);
  tileManager.addTile (yellowStart);

  mapDrawer.addRenderable (redStart);
  mapDrawer.addRenderable (blueStart);
  mapDrawer.addRenderable (greenStart);
  mapDrawer.addRenderable (yellowStart);

  // Finishing tiles
  for (int i = 1; i <= 5; i++) {
    // ALARM Я ТУТ НЕ РУХАВ ПОЗИШИН, ЛИШИВ ЯК Є!
    auto redFinish = std::make_shared<PrefinishingTile> (
        Dimensions (i, 7, 1, 1), 200 + i, i, red, 1);
    auto blueFinish = std::make_shared<PrefinishingTile> (
        Dimensions (7, i, 1, 1), 300 + i, i, blue, 3);
    auto greenFinish = std::make_shared<PrefinishingTile> (
        Dimensions (7, 14 - i, 1, 1), 400 + i, i, green,4);
    auto yellowFinish = std::make_shared<PrefinishingTile> (
        Dimensions (14 - i, 7, 1, 1), 500 + i, i, yellow,2);

    tileManager.addTile (redFinish);
    tileManager.addTile (blueFinish);
    tileManager.addTile (greenFinish);
    tileManager.addTile (yellowFinish);

    mapDrawer.addRenderable (redFinish);
    mapDrawer.addRenderable (blueFinish);
    mapDrawer.addRenderable (greenFinish);
    mapDrawer.addRenderable (yellowFinish);
  }
}

void leftClickHandler(double x, double y) {
    auto &mapDrawer = MapDrawer::getInstance();
    
    // Get the window size
    auto windowSize = WindowManager::getInstance().getWindowSize();
    int windowWidth = windowSize.first;
    int windowHeight = windowSize.second;

    // Convert from window coordinates to OpenGL coordinates
    float normalizedX = static_cast<float>(x) / 800 * 2.0f - 1.0f;
    float normalizedY = 1.0f - static_cast<float>(y) / 800 * 2.0f;

    // Find the renderable at the normalized coordinates
    auto renderable = mapDrawer.findByDimensionsRange(normalizedX, normalizedY);

    std::cout << "Left click at window coordinates (" << x << ", " << y << ")\n";
    std::cout << "Converted to OpenGL coordinates (" << normalizedX << ", " << normalizedY << ")\n";
    if (renderable) {
        std::cout << "Renderable found: " << renderable << " " << renderable->getZIndex() << " " << renderable->getDimensions() << std::endl;
    } else {
        std::cout << "No renderable found at the clicked position." << std::endl;
    }
}


int main () {
  std::cout << "Testing libraries..." << std::endl;

  // Test GLFW
  testGLFW ();

  // Test FreeType
  testFreeType ();

  // Test stb_image
  testStbImage ();

  std::cout << "All libraries tested successfully!" << std::endl;

  auto &mapDrawer = MapDrawer::getInstance ();

  /*(800, 15);*/

  Color blue = Color (0.004f, 0.725f, 0.945f);
  Color red = Color (0.996f, 0.180f, 0.090f);
  Color green = Color (0.29f, 0.729f, 0.29f);
  Color yellow = Color (1.0f, 0.784f, 0.208f);
  // Launch drawMap in a separate thread
  std::thread backgroundThread (&MapDrawer::drawMap, &mapDrawer);

  std::this_thread::sleep_for (std::chrono::seconds (1));
  // Detach the thread to allow it to run independently
  /*backgroundThread.detach();*/
  /*mapDrawer.enqueueRenderTask([&]() { mapDrawer.drawBase(9, 9, green); });*/
  // Draw something one time
  /*mapDrawer.drawBase(9, 9, green); // Green*/
  // mapDrawer.drawMap();

  /*return 0;*/
  // Create the event dispatcher
  EventDispatcher dispatcher;

  // Create the event loop and pass the dispatcher to it
  EventLoop eventLoop (dispatcher);
  Board board;

  // Create default colors
  // Color red("#E4080A");
  // Color yellow("#FFDE59");
  // Color blue("#0342C8");
  // Color green("#7DDA58");

  // Create default teams
  Team teamRed (red, 1);
  Team teamYellow (yellow, 2);
  Team teamBlue (blue, 3);
  Team teamGreen (green, 4);
  auto &teamManager = TeamManager::getInstance ();
  teamManager.addTeam (teamRed);
  teamManager.addTeam (teamGreen);
  teamManager.addTeam (teamYellow);
  teamManager.addTeam (teamBlue);

  Dimensions dimensions (0, 9, 6, 6);

  std::cout << "aboba" << std::endl;

  // Base redBase(dimensions, red, 1, 10);
  //
  auto &baseManager = BaseManager::getInstance ();
  auto redBase = std::make_shared<Base> (Dimensions (0, 9, 6, 6), red, 1, 1);
  mapDrawer.addRenderable (redBase);
  baseManager.addBase(1, redBase);

  auto blueBase = std::make_shared<Base> (Dimensions (0, 0, 6, 6), blue, 3, 20);
  mapDrawer.addRenderable (blueBase);
  baseManager.addBase (blueBase->getTeamId (), blueBase);

  auto greenBase = std::make_shared<Base> (Dimensions (9, 9, 6, 6), green, 4, 30);
  mapDrawer.addRenderable (greenBase);
  baseManager.addBase (greenBase->getTeamId (), greenBase);

  auto yellowBase = std::make_shared<Base> (Dimensions (9, 0, 6, 6), yellow, 2, 40);
  mapDrawer.addRenderable (yellowBase);

  baseManager.addBase (yellowBase->getTeamId (), yellowBase);
  /*redBase.skibidi();*/
  /*redBase.renderSelf();*/

  // Create default players
  Player redPlayer (1, 1);
  Player yellowPlayer (2, 2);
  Player bluePlayer (3, 3);
  Player greenPlayer (4, 4);

  // Create TurnManager
  TurnManager turnManager (eventLoop);
  PawnManager pawnManager;

  // Create event handlers
  auto rollDiceHandler = std::make_shared<RollDiceHandler> (turnManager, eventLoop);
  auto movePawnHandler = std::make_shared<MovePawnHandler>(board, pawnManager);
  auto stopGameHandler = std::make_shared<StopGameHandler> ();
  auto playerTurnHandler = std::make_shared<PlayerTurnHandler> (eventLoop, 4, turnManager);
  dispatcher.subscribe("MovePawnEvent", movePawnHandler);
  auto randomAssPawn = std::make_shared<Pawn> (10,
      1,
      1,
      Dimensions (0, 9, 0.45, 0.45),
      red);
  pawnManager.addPawn (randomAssPawn);
  randomAssPawn->setContext (TileContext::Base);
  mapDrawer.addRenderable (randomAssPawn);

  glfwMakeContextCurrent(mapDrawer.window);

  ClickHandler clickHandler(mapDrawer.window);
  clickHandler.registerClickCallback(GLFW_MOUSE_BUTTON_LEFT, leftClickHandler);

  initializeTiles ();

  

  /*int idCounter = 0;*/
  /*for (int playerId = 1; playerId <= 4; ++playerId) {*/
  /*  for (int pawnId = 1; pawnId <= 4; ++pawnId) {*/
  /*    // TODO: Replace the magical number 9 with actualy tile id. Each base
   * has*/
  /*    // 4 tiles, so some of those tiles should be assigned to each pawn*/
  /*    auto pawn = Pawn(idCounter, 0, Dimensions(0, 0, 1, 1),*/
  /*                     teamManager.getTeamById(playerId).color);*/
  /*    pawnManager.addPawn(pawn); // All pawns start at tile ID 0*/
  /*    idCounter++;*/
  /*  }*/
  /*}*/

  // Subscribe handlers to specific events
  /*dispatcher.subscribe("RollDiceEvent", rollDiceHandler);*/
  /*dispatcher.subscribe("MovePawnEvent", movePawnHandler);*/
  /*dispatcher.subscribe("StopGameEvent", stopGameHandler);*/
  /*dispatcher.subscribe("PlayerTurnEvent", playerTurnHandler);*/

  // Start the first player's turn using TurnManager
  /*turnManager.startTurn(1, [&eventLoop]() {*/
  /*  std::cout << "All turns finished. Enqueueing StopGameEvent...\n";*/
  /*  eventLoop.enqueueEvent(std::make_shared<StopGameEvent>());*/
  /*});*/

  // Process all events in the loop
  
  /*eventLoop.processEvents();*/
  eventLoop.start();

  std::this_thread::sleep_for (std::chrono::seconds (1));
  eventLoop.enqueueEvent(std::make_shared<MovePawnEvent>(1, 10, 6));


  std::this_thread::sleep_for (std::chrono::seconds (2));
  eventLoop.enqueueEvent(std::make_shared<MovePawnEvent>(1, 10, 3));

  // std::this_thread::sleep_for (std::chrono::seconds (2));
  // eventLoop.enqueueEvent(std::make_shared<MovePawnEvent>(1, 10, 5));
  // std::this_thread::sleep_for (std::chrono::seconds (2));
  // eventLoop.enqueueEvent(std::make_shared<MovePawnEvent>(1, 10, 5));
  // std::this_thread::sleep_for (std::chrono::seconds (2));
  // eventLoop.enqueueEvent(std::make_shared<MovePawnEvent>(1, 10, 5));
  // std::this_thread::sleep_for (std::chrono::seconds (2));
  // eventLoop.enqueueEvent(std::make_shared<MovePawnEvent>(1, 10, 5));
  // std::this_thread::sleep_for (std::chrono::seconds (2));
  // eventLoop.enqueueEvent(std::make_shared<MovePawnEvent>(1, 10, 5));
  // std::this_thread::sleep_for (std::chrono::seconds (2));
  // eventLoop.enqueueEvent(std::make_shared<MovePawnEvent>(1, 10, 5));
  // std::this_thread::sleep_for (std::chrono::seconds (2));
  // eventLoop.enqueueEvent(std::make_shared<MovePawnEvent>(1, 10, 5));
  // std::this_thread::sleep_for (std::chrono::seconds (2));
  // eventLoop.enqueueEvent(std::make_shared<MovePawnEvent>(1, 10, 5));
  //  std::this_thread::sleep_for (std::chrono::seconds (2));
  // eventLoop.enqueueEvent(std::make_shared<MovePawnEvent>(1, 10, 5));
  //  std::this_thread::sleep_for (std::chrono::seconds (2));
  // eventLoop.enqueueEvent(std::make_shared<MovePawnEvent>(1, 10, 5));
  //  std::this_thread::sleep_for (std::chrono::seconds (2));
  // eventLoop.enqueueEvent(std::make_shared<MovePawnEvent>(1, 10, 5));
  //  std::this_thread::sleep_for (std::chrono::seconds (2));
  // eventLoop.enqueueEvent(std::make_shared<MovePawnEvent>(1, 10, 5));

  // std::this_thread::sleep_for (std::chrono::seconds (2));
  // eventLoop.enqueueEvent(std::make_shared<MovePawnEvent>(1, 10, 2));

  /*eventLoop.stop();*/
  while (true) {
  }
  return 0;
}
