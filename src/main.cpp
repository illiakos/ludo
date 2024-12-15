#include "Board.h"
#include "Color.h"
#include "EventDispatcher.h"
#include "EventLoop.h"
#include "MovePawnEvent.h"
#include "MovePawnHandler.h"
#include "Player.h"
#include "PlayerTurnEvent.h"
#include "PlayerTurnHandler.h"
#include "RollDiceHandler.h"
#include "StopGameEvent.h"
#include "StopGameHandler.h"
#include "Team.h"
#include "TurnManager.h"
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include <iostream>
#include <memory>
#include <ostream>
#include FT_FREETYPE_H
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "MapDrawer.h"

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

int main() {
  std::cout << "Testing libraries..." << std::endl;

  // Test GLFW
  testGLFW();

  // Test FreeType
  testFreeType();

  // Test stb_image
  testStbImage();

  std::cout << "All libraries tested successfully!" << std::endl;

  MapDrawer mapDrawer = MapDrawer(800, 15);

  mapDrawer.drawMap();

  return 0;
  // Create the event dispatcher
  EventDispatcher dispatcher;

  // Create the event loop and pass the dispatcher to it
  EventLoop eventLoop(dispatcher);
  Board board;

  // Create default colors
  Color red("#E4080A");
  Color yellow("#FFDE59");
  Color blue("#0342C8");
  Color green("#7DDA58");

  // Create default teams
  Team teamRed(red, 1);
  Team teamYellow(yellow, 2);
  Team teamBlue(blue, 3);
  Team teamGreen(green, 4);

  std::cout << "aboba" << std::endl;

  // Create default players
  Player redPlayer(1, 1);
  Player yellowPlayer(2, 2);
  Player bluePlayer(3, 3);
  Player greenPlayer(4, 4);

  // Create TurnManager
  TurnManager turnManager(eventLoop);
  PawnManager pawnManager;

  // Create event handlers
  auto rollDiceHandler =
      std::make_shared<RollDiceHandler>(turnManager, eventLoop);
  auto movePawnHandler = std::make_shared<MovePawnHandler>(board, pawnManager);
  auto stopGameHandler = std::make_shared<StopGameHandler>();
  auto playerTurnHandler =
      std::make_shared<PlayerTurnHandler>(eventLoop, 4, turnManager);

  for (int playerId = 1; playerId <= 4; ++playerId) {
    for (int pawnId = 1; pawnId <= 4; ++pawnId) {
      // TODO: Replace the magical number 9 with actualy tile id. Each base has
      // 4 tiles, so some of those tiles should be assigned to each pawn
      pawnManager.addPawn(pawnId, 9); // All pawns start at tile ID 0
    }
  }
  // Subscribe handlers to specific events
  dispatcher.subscribe("RollDiceEvent", rollDiceHandler);
  dispatcher.subscribe("MovePawnEvent", movePawnHandler);
  dispatcher.subscribe("StopGameEvent", stopGameHandler);
  dispatcher.subscribe("PlayerTurnEvent", playerTurnHandler);

  // Start the first player's turn using TurnManager
  turnManager.startTurn(1, [&eventLoop]() {
    std::cout << "All turns finished. Enqueueing StopGameEvent...\n";
    eventLoop.enqueueEvent(std::make_shared<StopGameEvent>());
  });

  // Process all events in the loop
  std::cout << "Starting game loop...\n";
  eventLoop.processEvents();
  std::cout << "Game loop ended.\n";

  return 0;
}
