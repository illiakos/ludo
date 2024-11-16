#include "WaitForChoosePawnEvent.h"
#include "MovePawnEvent.h"
#include "WaitForChoosePawnHandler.h"
#include <iostream>
#include <memory>

void WaitForChoosePawnHandler::handleEvent(const std::shared_ptr<Event>& event) {
    auto choosePawnEvent = std::dynamic_pointer_cast<WaitForChoosePawnEvent>(event);
    if (choosePawnEvent) {
        std::cout << "Player " << choosePawnEvent->playerId << " needs to choose a pawn.\n";

        // Example GUI interaction (to be replaced by actual GUI code):
        int selectedPawnId = 1; // Mocking a pawn selection (this would be user input)

        // Enqueue the MovePawnEvent with the selected pawn and dice roll result
        eventLoop.enqueueEvent(std::make_shared<MovePawnEvent>(choosePawnEvent->playerId, selectedPawnId, choosePawnEvent->diceRollResult));

        // Notify TurnManager to wait for the move to complete
        turnManager.endTurn();
    }
}
