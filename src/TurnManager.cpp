#include "TurnManager.h"
#include "RollDiceEvent.h"
#include <iostream>

TurnManager::TurnManager(EventLoop &loop)
    : eventLoop(loop), currentPlayerId(0), totalPlayers(0),
      gameOverCallback(nullptr) {}

void TurnManager::startTurn(int startingPlayer,
                            std::function<void()> onGameOver) {
  currentPlayerId = startingPlayer;
  gameOverCallback = onGameOver;
  totalPlayers = 4; // For simplicity, assuming 4 players
  startPlayerTurn();
}

void TurnManager::endTurn() {
  // Move to the next player
  currentPlayerId = (currentPlayerId + 1) % totalPlayers;

  if (currentPlayerId == 0 && gameOverCallback) {
    std::cout << "All turns completed. Ending game.\n";
    gameOverCallback();
  } else {
    startPlayerTurn();
  }
}

int TurnManager::getCurrentPlayerId() const { return currentPlayerId; }

void TurnManager::startPlayerTurn() {
  std::cout << "Player " << currentPlayerId << "'s turn starts.\n";

  // Enqueue a RollDiceEvent to start the player's turn
  eventLoop.enqueueEvent(std::make_shared<RollDiceEvent>(currentPlayerId));
}
