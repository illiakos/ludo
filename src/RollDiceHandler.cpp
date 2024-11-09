

#include "RollDiceHandler.h"
#include "RollDiceEvent.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

void RollDiceHandler::handleEvent(const std::shared_ptr<Event> &event) {
  auto rollEvent = std::dynamic_pointer_cast<RollDiceEvent>(event);
  // Seed the random number generator
  std::srand(static_cast<unsigned int>(std::time(0)));

  // Generate a random number between 1 and 6
  int randomNumber = std::rand() % 6 + 1;

  if (rollEvent) {
    
    std::cout << "Player " << rollEvent->playerId << " rolled the " << randomNumber <<
        " !\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
  }
}

/*class RollDiceHandler : public EventHandler {*/
/*public:*/
/*    void handleEvent(const std::shared_ptr<Event>& event) override {*/
/*        auto rollEvent = std::dynamic_pointer_cast<RollDiceEvent>(event);*/
/*        if (rollEvent) {*/
/*            std::cout << "Player " << rollEvent->playerId << " rolled the
 * dice!\n";*/
/*        }*/
/*    }*/
/*};*/
