
#include "PlayerTurnHandler.h"
#include "EventHandler.h"
#include "PlayerTurnEvent.h"
#include <iostream>
#include <memory>
#include "RollDiceEvent.h"

PlayerTurnHandler::PlayerTurnHandler(EventLoop& loop, int totalPlayers)
  : EventHandler("PlayerTurnHandler"), eventLoop(loop), totalPlayers(totalPlayers) {}



void PlayerTurnHandler::handleEvent(const std::shared_ptr<Event>& event) {
    auto turnEvent = std::dynamic_pointer_cast<PlayerTurnEvent>(event);
    if (turnEvent) {
        int playerId = turnEvent->playerId;
        std::cout << "It's Player " << playerId << "'s turn.\n";

        // Trigger a dice roll for this player
        /*eventLoop.enqueueEvent(std::make_shared<RollDiceEvent>(playerId));*/
        this->eventLoop.enqueueEvent(std::make_shared<RollDiceEvent>(playerId));

        // Schedule the next player's turn
        int nextPlayerId = (playerId + 1) % totalPlayers;
        eventLoop.enqueueEvent(std::make_shared<PlayerTurnEvent>(nextPlayerId));
    }
}
