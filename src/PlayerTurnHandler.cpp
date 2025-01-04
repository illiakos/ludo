#include "PlayerTurnHandler.hpp"
#include "EndTurnEvent.hpp"
#include "EventLoop.hpp"
#include "MovePawnEvent.hpp"
#include "PlayerTurnEvent.hpp"
#include "RollDiceEvent.hpp"
#include "TurnManager.hpp"
#include <iostream>
#include <memory>
#include "DiceClickEvent.hpp"

/*PlayerTurnHandler::PlayerTurnHandler(std::shared_ptr<EventLoop> loop, int totalPlayers, TurnManager& turnManager) {*/
/**/
/*}*/
/**/
void PlayerTurnHandler::handleEvent(const std::shared_ptr<Event> &event) {
    auto turnEvent = std::dynamic_pointer_cast<PlayerTurnEvent>(event);
    if (turnEvent) {
        int playerId = turnEvent->playerId;
        std::cout << "Current player ID: " << playerId << std::endl;

        // Set current player turn
        currentPlayerTurnEvent = turnEvent;

        // Start turn
        turnManager.startTurn(playerId, [this, playerId]() {
            // Next player's turn will only be enqueued after the current turn ends
            int nextPlayerId = (playerId + 1) % totalPlayers;
            eventLoop->enqueueEvent(std::make_shared<PlayerTurnEvent>(nextPlayerId));
        });
    }

    /*auto diceClickEvent = std::dynamic_pointer_cast<DiceClickEvent>(event);*/
    /*if (diceClickEvent) {*/
    /*    std::cout << "Player clicked the dice.\n";*/
    /*    int rolledValue = rollDice(); // Example dice roll logic*/
    /*    turnManager.setCurrentRolledValue(rolledValue);*/
    /*    std::cout << "Rolled value: " << rolledValue << std::endl;*/
    /*}*/

    auto movePawnEvent = std::dynamic_pointer_cast<MovePawnEvent>(event);
    if (movePawnEvent) {
        std::cout << "Player moved a pawn.\n";

        // Update game state with pawn movement
        /*turnManager.movePawn(movePawnEvent->getPawnId(), movePawnEvent->getTargetPosition());*/

        // End the current turn
        if (currentPlayerTurnEvent) {
            currentPlayerTurnEvent->completeTurn();
        }
    }

    auto endTurnEvent = std::dynamic_pointer_cast<EndTurnEvent>(event);
    if (endTurnEvent) {
        std::cout << "Ending turn for current player.\n";
        turnManager.endTurn();
        if (currentPlayerTurnEvent) {
            currentPlayerTurnEvent->completeTurn();
        }
    }
}
