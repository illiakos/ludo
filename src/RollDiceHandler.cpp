

#include "RollDiceHandler.h"
#include "EventHandler.h"
#include "RollDiceEvent.h"
#include <iostream>
#include <memory>

void RollDiceHandler::handleEvent(const std::shared_ptr<Event>& event)  {
        auto rollEvent = std::dynamic_pointer_cast<RollDiceEvent>(event);
        if (rollEvent) {
            std::cout << "Player " << rollEvent->playerId << " rolled the dice!\n";
        }
}

/*class RollDiceHandler : public EventHandler {*/
/*public:*/
/*    void handleEvent(const std::shared_ptr<Event>& event) override {*/
/*        auto rollEvent = std::dynamic_pointer_cast<RollDiceEvent>(event);*/
/*        if (rollEvent) {*/
/*            std::cout << "Player " << rollEvent->playerId << " rolled the dice!\n";*/
/*        }*/
/*    }*/
/*};*/
