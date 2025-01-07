#include "Base.hpp"
#include "BaseManager.hpp"
#include "Board.hpp"
#include "ClickHandler.hpp"
#include "Color.hpp"
#include "ColorConstants.hpp"
#include "Dice.hpp"
#include "Dimensions.hpp"
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
#include "WindowManager.hpp"
#include <GLFW/glfw3.h>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <ft2build.h>
#include <iostream>
#include <memory>
#include <ostream>
#include FT_FREETYPE_H
#define STB_IMAGE_IMPLEMENTATION
#include "MapDrawer.hpp"
#include "stb_image.h"
#include <thread>

void testGLFW() {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW!" << std::endl;
    exit(EXIT_FAILURE);
  }

  GLFWwindow *window =
      glfwCreateWindow(800, 600, "GLFW Test Window", NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create GLFW window!" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  std::cout << "GLFW initialized successfully!" << std::endl;

  // Close immediately for testing
  glfwDestroyWindow(window);
  glfwTerminate();
}

// Function to test FreeType
void testFreeType() {
  FT_Library ft;
  if (FT_Init_FreeType(&ft)) {
    std::cerr << "Failed to initialize FreeType!" << std::endl;
    exit(EXIT_FAILURE);
  }

  // Load a font file (use any TTF file you have)
  FT_Face face;
  if (FT_New_Face(ft, "../src/assets/fonts/OpenSans-Regular.ttf", 0, &face)) {
    std::cerr << "Failed to load font!" << std::endl;
    FT_Done_FreeType(ft);
    exit(EXIT_FAILURE);
  }

  std::cout << "FreeType initialized and font loaded successfully!"
            << std::endl;

  // Cleanup
  FT_Done_Face(face);
  FT_Done_FreeType(ft);
}

// Function to test stb_image
void testStbImage() {
  int width, height, channels;
  unsigned char *data =
      stbi_load("../src/assets/images/test.jpg", &width, &height, &channels, 0);
  if (!data) {
    std::cerr << "Failed to load image with stb_image!" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "Image loaded successfully with stb_image! Dimensions: " << width
            << "x" << height << ", Channels: " << channels << std::endl;

  stbi_image_free(data);
}

void addWalkableTile(TileManager &tileManager, MapDrawer &mapDrawer, int x,
                     int y, int &position) {
  auto walkableTile =
      std::make_shared<Tile>(Dimensions(x, y, 1, 1), position, position,
                             Color(0.8f, 0.8f, 0.8f), TileContext::Walkable);
  tileManager.addTile(walkableTile);
  mapDrawer.addRenderable(walkableTile);
  position++;
}

void addSafeTile(TileManager &tileManager, MapDrawer &mapDrawer, int x, int y,
                 int position, const Color color) {
  auto safeTile = std::make_shared<SafeTile>(Dimensions(x, y, 1, 1), position,
                                             position, color);
  tileManager.addTile(safeTile);
  mapDrawer.addRenderable(safeTile);
}

void addTransitionTile(TileManager &tileManager, MapDrawer &mapDrawer, int x,
                       int y, int position, int transitionFrom,
                       int transitionTo, const Color &color) {
  auto transitionTile = std::make_shared<TransitionTile>(
      Dimensions(x, y, 1, 1), position, position, transitionFrom, transitionTo,
      color);
  tileManager.addTile(transitionTile);
  mapDrawer.addRenderable(transitionTile);
}

void addStartingTile(TileManager &tileManager, MapDrawer &mapDrawer, int x,
                     int y, int position, const Color color, int team) {
  auto startingTile = std::make_shared<StartingTile>(
      Dimensions(x, y, 1, 1), position, position, color, team);
  tileManager.addTile(startingTile);
  mapDrawer.addRenderable(startingTile);
}

void addFinishingTile(TileManager &tileManager, MapDrawer &mapDrawer, int x,
                      int y, int id, int position, const Color &color,
                      int team) {
  auto finishingTile = std::make_shared<PrefinishingTile>(
      Dimensions(x, y, 1, 1), id, position, color, team);
  tileManager.addTile(finishingTile);
  mapDrawer.addRenderable(finishingTile);
}

void skipPosition(int &position, int skipCount = 1) { position += skipCount; }

void createWalkableTiles(TileManager &tileManager, MapDrawer &mapDrawer) {
  int position = 2;

  // Walkable tiles for horizontal path (x = 2 to 5)
  for (int x = 2; x <= 5; x++) {
    addWalkableTile(tileManager, mapDrawer, x, 8, position);
  }

  // Walkable tiles for vertical path (y = 9 to 15, skipping y = 12)
  for (int y = 9; y <= 14; y++) {
    if (y == 12) {
      skipPosition(position); // Skip safe tile
      continue;
    }
    addWalkableTile(tileManager, mapDrawer, 6, y, position);
  }

  // Green transition position
  skipPosition(position, 1);
  addWalkableTile(tileManager, mapDrawer, 8, 14, position);

  skipPosition(position, 1);

  // Walkable tiles for descending vertical path (y = 12 to 9)
  for (int y = 12; y >= 9; y--) {
    addWalkableTile(tileManager, mapDrawer, 8, y, position);

  }

  // Walkable tiles for horizontal path (x = 9 to 14, skipping x = 12)
  for (int x = 9; x <= 14; x++) {
    if (x == 12) {
      skipPosition(position); // Skip safe tile
      continue;
    }
    addWalkableTile(tileManager, mapDrawer, x, 8, position);
  }

  // Yellow transition positions
  skipPosition(position, 1);
  addWalkableTile(tileManager, mapDrawer, 14, 6, position);
  // Yellow start positions
  skipPosition(position, 1);

  // Walkable tiles for horizontal path (x = 12 to 9)
  for (int x = 12; x >= 9; x--) {
    addWalkableTile(tileManager, mapDrawer, x, 6, position);
  }

  // Walkable tiles for vertical path (y = 5 to 0, skipping y = 2)
  for (int y = 5; y >= 0; y--) {
    if (y == 2) {
      skipPosition(position); // Skip safe tile
      continue;
    }
    addWalkableTile(tileManager, mapDrawer, 8, y, position);
  }

  // Blue transition position
  skipPosition(position, 1);
  addWalkableTile(tileManager, mapDrawer, 6, 0, position);
  // Blue start position
  skipPosition(position, 1);

  // Walkable tiles for ascending vertical path (y = 2 to 5)
  for (int y = 2; y <= 5; y++) {
    addWalkableTile(tileManager, mapDrawer, 6, y, position);
  }

  // Walkable tiles for horizontal path (x = 5 to 0, skipping x = 2)
  for (int x = 5; x >= 0; x--) {
    if (x == 2) {
      
      skipPosition(position, 1); // Skip safe tile
      continue;
    }
    
    addWalkableTile(tileManager, mapDrawer, x, 6, position);
    
  }
  std::cout << "+++++++++++++++++++" << std::endl;
  std::cout << "Position " << position << std::endl;

  std::cout << "+++++++++++++++++++" << std::endl;
  // Red transition position
  skipPosition(position);
  addWalkableTile(tileManager, mapDrawer, 0, 8, position);
}

void createSafeTiles(TileManager &tileManager, MapDrawer &mapDrawer) {
  addSafeTile(tileManager, mapDrawer, 6, 12, 9, red);    // Red Safe Tile
  addSafeTile(tileManager, mapDrawer, 2, 6, 48, blue);   // Blue Safe Tile
  addSafeTile(tileManager, mapDrawer, 12, 8, 22, green); // Green Safe Tile
  addSafeTile(tileManager, mapDrawer, 8, 2, 35, yellow); // Yellow Safe Tile
}

void createTransitionTiles(TileManager &tileManager, MapDrawer &mapDrawer) {
  addTransitionTile(tileManager, mapDrawer, 0, 7, 51, 1, 1,
                    Color(0.8f, 0.8f, 0.8f)); // Red Transition Tile
  addTransitionTile(tileManager, mapDrawer, 7, 0, 38, 2, 2,
                    Color(0.8f, 0.8f, 0.8f)); // Blue Transition Tile
  addTransitionTile(tileManager, mapDrawer, 7, 14, 12, 3, 3,
                    Color(0.8f, 0.8f, 0.8f)); // Green Transition Tile
  addTransitionTile(tileManager, mapDrawer, 14, 7, 25, 4, 4,
                    Color(0.8f, 0.8f, 0.8f)); // Yellow Transition Tile
}

void createStartingTiles(TileManager &tileManager, MapDrawer &mapDrawer) {
  addStartingTile(tileManager, mapDrawer, 1, 8, 1, red, 1); // Red Starting Tile
  addStartingTile(tileManager, mapDrawer, 6, 1, 40, blue,
                  3); // Blue Starting Tile
  addStartingTile(tileManager, mapDrawer, 8, 13, 14, green,
                  4); // Green Starting Tile
  addStartingTile(tileManager, mapDrawer, 13, 6, 27, yellow,
                  2); // Yellow Starting Tile
}

void createFinishingTiles(TileManager &tileManager, MapDrawer &mapDrawer) {
  for (int i = 1; i <= 5; i++) {
    // Red Finishing Tile
    addFinishingTile(tileManager, mapDrawer, i, 7, 200 + i, i, red, 1);

    // Blue Finishing Tile
    addFinishingTile(tileManager, mapDrawer, 7, i, 300 + i, i, blue, 3);

    // Green Finishing Tile
    addFinishingTile(tileManager, mapDrawer, 7, 14 - i, 400 + i, i, green, 4);

    // Yellow Finishing Tile
    addFinishingTile(tileManager, mapDrawer, 14 - i, 7, 500 + i, i, yellow, 2);
  }
}

void initializeTiles() {
  TileManager &tileManager = TileManager::getInstance();
  MapDrawer &mapDrawer = MapDrawer::getInstance();

  createWalkableTiles(tileManager, mapDrawer);

  createSafeTiles(tileManager, mapDrawer);

  createTransitionTiles(tileManager, mapDrawer);

  createStartingTiles(tileManager, mapDrawer);

  createFinishingTiles(tileManager, mapDrawer);

  auto dice = std::make_shared<Dice>(Dimensions(7, 7, 1, 1));
  mapDrawer.addRenderable(dice);
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
  std::cout << "Converted to OpenGL coordinates (" << normalizedX << ", "
            << normalizedY << ")\n";
  if (renderable) {
    std::cout << "Renderable found: " << renderable << " "
              << renderable->getZIndex() << " " << renderable->getDimensions()
              << std::endl;
    renderable->onClick();
  } else {
    std::cout << "No renderable found at the clicked position." << std::endl;
  }
}

int main() {

  std::cout << "Testing libraries..." << std::endl;

  // Test GLFW
  testGLFW();

  // Test FreeType
  testFreeType();

  // Test stb_image
  testStbImage();

  std::cout << "All libraries tested successfully!" << std::endl;

  auto &mapDrawer = MapDrawer::getInstance();

  /*(800, 15);*/

  Color blue = Color(0.004f, 0.725f, 0.945f);
  Color red = Color(0.996f, 0.180f, 0.090f);
  Color green = Color(0.29f, 0.729f, 0.29f);
  Color yellow = Color(1.0f, 0.784f, 0.208f);
  // Launch drawMap in a separate thread
  std::thread backgroundThread(&MapDrawer::drawMap, &mapDrawer);

  std::this_thread::sleep_for(std::chrono::seconds(1));
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
  auto eventLoop = std::make_shared<EventLoop>(dispatcher);
  eventLoop->setInstance(*eventLoop);
  /*EventLoop eventLoop(dispatcher);*/
  Board board;

  // Create default colors
  // Color red("#E4080A");
  // Color yellow("#FFDE59");
  // Color blue("#0342C8");
  // Color green("#7DDA58");

  // Create default teams
  Team teamRed(red, 1);
  Team teamYellow(yellow, 2);
  Team teamBlue(blue, 3);
  Team teamGreen(green, 4);
  auto &teamManager = TeamManager::getInstance();
  teamManager.addTeam(teamRed);
  teamManager.addTeam(teamGreen);
  teamManager.addTeam(teamYellow);
  teamManager.addTeam(teamBlue);

  Dimensions dimensions(0, 9, 6, 6);

  std::cout << "aboba" << std::endl;

  // Base redBase(dimensions, red, 1, 10);
  //
  auto &baseManager = BaseManager::getInstance();
  auto redBase = std::make_shared<Base>(Dimensions(0, 9, 6, 6), red, 1, 1);
  mapDrawer.addRenderable(redBase);
  baseManager.addBase(1, redBase);

  auto blueBase = std::make_shared<Base>(Dimensions(0, 0, 6, 6), blue, 3, 20);
  mapDrawer.addRenderable(blueBase);
  baseManager.addBase(blueBase->getTeamId(), blueBase);

  auto greenBase = std::make_shared<Base>(Dimensions(9, 9, 6, 6), green, 4, 30);
  mapDrawer.addRenderable(greenBase);
  baseManager.addBase(greenBase->getTeamId(), greenBase);

  auto yellowBase =
      std::make_shared<Base>(Dimensions(9, 0, 6, 6), yellow, 2, 40);
  mapDrawer.addRenderable(yellowBase);

  baseManager.addBase(yellowBase->getTeamId(), yellowBase);
  /*redBase.skibidi();*/
  /*redBase.renderSelf();*/

  // Create default players
  Player redPlayer(1, 1);
  Player yellowPlayer(2, 2);
  Player bluePlayer(3, 3);
  Player greenPlayer(4, 4);

  // Create TurnManager
  TurnManager turnManager(eventLoop);

  TurnManager::setInstance(turnManager);

  PawnManager pawnManager;

  // Create event handlers
  auto rollDiceHandler =
      std::make_shared<RollDiceHandler>(turnManager, eventLoop);
  auto movePawnHandler = std::make_shared<MovePawnHandler>(board, pawnManager);
  auto stopGameHandler = std::make_shared<StopGameHandler>();
  auto playerTurnHandler =
      std::make_shared<PlayerTurnHandler>(eventLoop, 4, turnManager);

  dispatcher.subscribe("PlayerTurnEvent", playerTurnHandler);
  dispatcher.subscribe("EndTurnEvent", playerTurnHandler);
  dispatcher.subscribe("MovePawnEvent", movePawnHandler);
  auto randomAssPawn =
      std::make_shared<Pawn>(10, 1, 1, Dimensions(0, 9, 0.45, 0.45), red);
  pawnManager.addPawn(randomAssPawn);
  randomAssPawn->setContext(TileContext::Base);
  mapDrawer.addRenderable(randomAssPawn);

  glfwMakeContextCurrent(mapDrawer.window);

  ClickHandler clickHandler(mapDrawer.window);
  clickHandler.registerClickCallback(GLFW_MOUSE_BUTTON_LEFT, leftClickHandler);

  initializeTiles();

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
  
  int idCounter = 1;
  for (int j=1;j<=4;j++) {
  
    auto newPawn = std::make_shared<Pawn>(idCounter, 1,3, Dimensions(9,9,0.45,0.45),teamManager.getTeamById(3).color);
    pawnManager.addPawn(newPawn);
    newPawn->setContext(TileContext::Base);
    mapDrawer.addRenderable(newPawn);
    idCounter++;
  }

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
  eventLoop->start();
  /**/
  /*std::this_thread::sleep_for(std::chrono::seconds(1));*/
  /*eventLoop->enqueueEvent(std::make_shared<MovePawnEvent>(1, 10, 6));*/
  /**/
  /*std::this_thread::sleep_for(std::chrono::seconds(2));*/
  /*eventLoop->enqueueEvent(std::make_shared<MovePawnEvent>(1, 10, 3));*/
  /**/

  /**/
  /*std::this_thread::sleep_for(std::chrono::seconds(2));*/
  /*eventLoop->enqueueEvent(std::make_shared<MovePawnEvent>(1, 10, 6));*/
  /*std::this_thread::sleep_for(std::chrono::seconds(4));*/
  std::cout << "Enqueued player turn" << std::endl;
  eventLoop->enqueueEvent(std::make_shared<PlayerTurnEvent>(1)); 

  /*for (int i = 0; i < 51; i++) {*/
  /**/
  /*  std::this_thread::sleep_for(std::chrono::milliseconds(500));*/
  /*  eventLoop->enqueueEvent(std::make_shared<MovePawnEvent>(1, 10, 1));*/
  /*}*/

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
