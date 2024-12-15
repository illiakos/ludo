#ifndef WAIT_FOR_CHOOSE_PAWN_HANDLER_H
#define WAIT_FOR_CHOOSE_PAWN_HANDLER_H

#include "EventHandler.hpp"
#include "TurnManager.hpp"
#include "EventLoop.hpp"

class WaitForChoosePawnHandler : public EventHandler {
public:
    WaitForChoosePawnHandler(TurnManager& turnManager, EventLoop& eventLoop)
        : EventHandler("WaitForChoosePawnHandler"), turnManager(turnManager), eventLoop(eventLoop) {}

    void handleEvent(const std::shared_ptr<Event>& event) override;

private:
    TurnManager& turnManager;
    EventLoop& eventLoop;
};

#endif // WAIT_FOR_CHOOSE_PAWN_HANDLER_H
