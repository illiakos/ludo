#include "RollDiceHandler.h"
#include "RollDiceEvent.h"
#include "WaitForChoosePawnEvent.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
void RollDiceHandler::handleEvent(const std::shared_ptr<Event>& event) {
    auto rollEvent = std::dynamic_pointer_cast<RollDiceEvent>(event);
    if (rollEvent) {
        std::cout << "Player " << rollEvent->playerId << " rolls the dice...\n";

        // Generate a random number between 1 and 6
        std::srand(static_cast<unsigned int>(std::time(0)));
        int rollResult = std::rand() % 6 + 1;

        std::cout << "Player " << rollEvent->playerId << " rolled a " << rollResult << "!\n";

        // Enqueue WaitForChoosePawnEvent
        eventLoop.enqueueEvent(std::make_shared<WaitForChoosePawnEvent>(rollEvent->playerId, rollResult));
    }
}
