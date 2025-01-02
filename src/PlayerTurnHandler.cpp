#include "PlayerTurnHandler.hpp"
#include "EndTurnEvent.hpp"
#include "EventLoop.hpp"
#include "PlayerTurnEvent.hpp"
#include "RollDiceEvent.hpp"
#include "TurnManager.hpp"
#include <iostream>
#include <memory>

PlayerTurnHandler::PlayerTurnHandler(EventLoop &loop, int totalPlayers,
                                     TurnManager &turnManager)
    : EventHandler("PlayerTurnHandler"), eventLoop(loop),
      totalPlayers(totalPlayers), turnManager(turnManager) {}

void PlayerTurnHandler::handleEvent(const std::shared_ptr<Event> &event) {
  auto turnEvent = std::dynamic_pointer_cast<PlayerTurnEvent>(event);
  if (turnEvent) {
    int playerId = turnEvent->playerId;
    turnManager.startTurn(playerId, [this, playerId]() {
      // Callback to enqueue the next turn once this turn ends
      int nextPlayerId = (playerId + 1) % totalPlayers;
      eventLoop.enqueueEvent(std::make_shared<PlayerTurnEvent>(nextPlayerId));
    });
  }

  auto endTurnEvent = std::dynamic_pointer_cast<EndTurnEvent>(event);
  if (endTurnEvent) {
    turnManager.endTurn();
  }
}
