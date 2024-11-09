
#include "MovePawnHandler.h"
#include <memory>

void MovePawnHandler::handleEvent(const std::shared_ptr<Event>& event) {

}

/*class MovePawnHandler : public EventHandler {*/
/*public:*/
/*    void handleEvent(const std::shared_ptr<Event>& event) override {*/
/*        auto moveEvent = std::dynamic_pointer_cast<MovePawnEvent>(event);*/
/*        if (moveEvent) {*/
/*            std::cout << "Player " << moveEvent->playerId << " moves pawn " */
/*                      << moveEvent->pawnId << " by " << moveEvent->stepsCount << " steps.\n";*/
/*        }*/
/*    }*/
/*};*/
