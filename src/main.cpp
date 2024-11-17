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
#include "TurnManager.cpp"
#include "TurnManager.h"
#include <iostream>
#include <memory>

int main() {
  // Create the event dispatcher
  EventDispatcher dispatcher;

  // Create the event loop and pass the dispatcher to it
  EventLoop eventLoop(dispatcher);

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
  auto movePawnHandler =
      std::make_shared<MovePawnHandler>(pawnManager, eventLoop);
  auto stopGameHandler = std::make_shared<StopGameHandler>();
  auto playerTurnHandler =
      std::make_shared<PlayerTurnHandler>(eventLoop, 4, turnManager);

  for (int playerId = 1; playerId <= 4; ++playerId) {
    for (int pawnId = 1; pawnId <= 4; ++pawnId) {
      pawnManager.addPawn(playerId, pawnId, 0); // All pawns start at tile ID 0
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
